#ifndef DB__QUOTE_upsert_avg_one_sec_variance
#define DB__QUOTE_upsert_avg_one_sec_variance

#include "quote.h"    // DB::Quote, upsert_avg_one_sec_variance_args_t
#include <libpq-fe.h> // PQescapeLiteral, PQfreemem
#include <stdio.h>    // snprintf
#include <string.h>   // strlen
#include <string>     // std::string, std::to_string

void DB::Quote::upsert_avg_one_sec_variance(
    const upsert_avg_one_sec_variance_args_t args) {
  const long int id = args.id;
  const std::string symbol = args.symbol;

  std::string find_quote_filter;

  if (id) {
    const char *query_format = R"(
      where
        id = %li
    )";

    const size_t query_l = strlen(query_format) + std::to_string(id).size();

    char query[query_l];

    snprintf(query, query_l, query_format, id);

    find_quote_filter = query;
  } else {
    char *sanitized_symbol =
        PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

    const char *query_format = R"(
      where
        symbol = upper(%s)
      order by
        timestamp desc
      limit 1
    )";

    const size_t query_l = strlen(query_format) + strlen(sanitized_symbol);

    char query[query_l];

    snprintf(query, query_l, query_format, sanitized_symbol);

    PQfreemem(sanitized_symbol);

    find_quote_filter = query;
  }

  const char *query_format = R"(
    with ref_quotes as (
      select
        id,
        symbol,
        timestamp
      from
        quotes
      %s
    ),
    ranked_quotes as (
      select
        rank() over (partition by ref_quotes.id order by quotes.timestamp asc) as i,
    ((quotes.ask + quotes.bid) * 0.5) as mid,
      ref_quotes.id as ref_id,
      ref_quotes.timestamp as ref_timestamp,
      quotes.symbol,
      quotes.timestamp
    from
      quotes
      join ref_quotes on ref_quotes.symbol = quotes.symbol
      where
        quotes.symbol = ref_quotes.symbol
        and quotes.timestamp >=(ref_quotes.timestamp - '3 minutes'::interval)
        and quotes.timestamp <= ref_quotes.timestamp
    ),
    one_sec_variances as (
      select
        current_quotes.ref_id,
        current_quotes.ref_timestamp,
        current_quotes.symbol,
        abs(next_quotes.mid - current_quotes.mid) /((extract(epoch from next_quotes.timestamp) - extract(epoch from current_quotes.timestamp))) as one_sec_variance
      from
        ranked_quotes as current_quotes
        join ranked_quotes as next_quotes on current_quotes.i = next_quotes.i - 1
          and current_quotes.ref_id = next_quotes.ref_id
    ),
    averages as (
      select
        avg(one_sec_variance),
        ref_id as quote_id,
        ref_timestamp as "timestamp",
        symbol
      from
        one_sec_variances
    group by
      ref_id,
      ref_timestamp,
      symbol)
      insert into avg_one_sec_variances(avg_one_sec_variance, quote_id, symbol, timestamp)(
        select
          coalesce(averages.avg, fallback.avg) as "avg",
          coalesce(averages.quote_id, fallback.quote_id) as quote_id,
          coalesce(averages.symbol, fallback.symbol) as symbol,
          coalesce(averages.timestamp, fallback.timestamp)
        from
          averages
        right join (
          select
            0 as "avg",
            id as quote_id,
            symbol,
            "timestamp"
          from
            ref_quotes) as fallback on true)
    on conflict (quote_id)
      do update set
        avg_one_sec_variance = excluded.avg_one_sec_variance
  )";

  const size_t query_l = strlen(query_format) + find_quote_filter.size();

  char query[query_l];

  snprintf(query, query_l, query_format, find_quote_filter.c_str());

  this->conn.exec(query, args.debug);
}

#endif
