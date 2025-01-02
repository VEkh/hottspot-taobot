#ifndef DB__POSITION_open
#define DB__POSITION_open

#include "position.h" // DB::Position
#include <libpq-fe.h> // PQescapeLiteral, PQfreemem
#include <stdio.h>    // snprintf
#include <string.h>   // strlen
#include <string>     // std::string, std::to_string

void DB::Position::open(const open_args_t args) {
  const double current_profit = args.current_profit;
  const double max_profit = args.max_profit;
  const double max_profit_at = args.max_profit_at;
  const double min_profit = args.min_profit;
  const double min_profit_at = args.min_profit_at;
  const double open_order_execution_mid = args.open_order_execution_mid;
  const double open_order_quantity = args.open_order_quantity;
  const double opened_at = args.opened_at;
  const double stop_loss = args.stop_loss;
  const double stop_profit = args.stop_profit;
  const double to_account_currency_ratio = args.to_account_currency_ratio;

  const std::string account_currency = args.account_currency;
  const std::string api_key_id = args.api_key_id;
  const std::string currency = args.currency;
  const std::string open_order_id = args.open_order_id;
  const std::string symbol = args.symbol;

  const char *query_format = R"(
    insert into positions(account_currency, api_key_id, currency, current_profit, max_profit, max_profit_at, min_profit, min_profit_at, open_order_execution_mid, open_order_id, open_order_quantity, opened_at, stop_loss, stop_profit, symbol, to_account_currency_ratio)
      values (%s, %s, %s, %f, %f, to_timestamp(%f), %f, to_timestamp(%f), %f, %s, %f, %s, %f, %f, %s, %f)
    on conflict (api_key_id, open_order_id)
      do update set
        current_profit = excluded.current_profit, max_profit = excluded.max_profit, max_profit_at = excluded.max_profit_at, min_profit = excluded.max_profit, min_profit_at = excluded.max_profit_at, stop_loss = excluded.stop_loss, stop_profit = excluded.stop_profit, to_account_currency_ratio = excluded.to_account_currency_ratio;
  )";

  char *sanitized_account_currency = PQescapeLiteral(
      this->conn.conn, account_currency.c_str(), account_currency.size());

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  char *sanitized_currency =
      PQescapeLiteral(this->conn.conn, currency.c_str(), currency.size());

  char *sanitized_open_order_id = PQescapeLiteral(
      this->conn.conn, open_order_id.c_str(), open_order_id.size());

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const std::string opened_at_str =
      opened_at ? std::string("to_timestamp(") + std::to_string(opened_at) + ")"
                : "now()";

  const size_t query_l =
      strlen(query_format) + strlen(sanitized_account_currency) +
      strlen(sanitized_api_key_id) + strlen(sanitized_currency) +
      std::to_string(current_profit).size() +
      std::to_string(max_profit).size() + std::to_string(max_profit_at).size() +
      std::to_string(min_profit).size() + std::to_string(min_profit_at).size() +
      std::to_string(open_order_execution_mid).size() +
      strlen(sanitized_open_order_id) +
      std::to_string(open_order_quantity).size() + opened_at_str.size() +
      std::to_string(stop_loss).size() + std::to_string(stop_profit).size() +
      strlen(sanitized_symbol) +
      std::to_string(to_account_currency_ratio).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_account_currency,
           sanitized_api_key_id, sanitized_currency, current_profit, max_profit,
           max_profit_at, min_profit, min_profit_at, open_order_execution_mid,
           sanitized_open_order_id, open_order_quantity, opened_at_str.c_str(),
           stop_loss, stop_profit, sanitized_symbol, to_account_currency_ratio);

  PQfreemem(sanitized_account_currency);
  PQfreemem(sanitized_api_key_id);
  PQfreemem(sanitized_currency);
  PQfreemem(sanitized_open_order_id);
  PQfreemem(sanitized_symbol);

  this->conn.exec(query, args.debug);
}

#endif
