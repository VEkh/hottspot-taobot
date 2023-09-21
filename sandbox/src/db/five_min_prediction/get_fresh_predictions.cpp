#ifndef DB__FIVE_MIN_PREDICTION_get_fresh_predictions
#define DB__FIVE_MIN_PREDICTION_get_fresh_predictions

#include "five_min_prediction.h" // DB::FiveMinPrediction, prediction_t, query_result_t
#include "result_to_predictions.cpp" // result_to_predictions
#include <libpq-fe.h>                // PQescapeLiteral, PQfreemem
#include <list>                      // std::list
#include <stdio.h>                   // snprintf
#include <string.h>                  // strlen
#include <string>                    // std::to_string
#include <time.h>                    // time

std::list<DB::FiveMinPrediction::prediction_t>
DB::FiveMinPrediction::get_fresh_predictions(
    const double ref_epoch = time(nullptr), const bool debug = false) {
  ;

  const char *query_format = R"(
    select
      *,
      extract(epoch from inserted_at) as inserted_at_epoch
    from
      five_min_predictions
    where
      symbol = %s
      and (to_timestamp(%f) - inserted_at) <= '5 minutes'::interval
  )";

  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, this->symbol.c_str(), this->symbol.size());

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol) +
                         std::to_string(ref_epoch).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbol, ref_epoch);

  PQfreemem(sanitized_symbol);

  const query_result_t result = this->conn.exec(query, debug);

  return result_to_predictions(result);
}

#endif
