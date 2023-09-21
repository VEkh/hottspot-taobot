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
      five_min_predictions.*,
      extract(epoch from five_min_predictions.inserted_at) as inserted_at_epoch,
      five_min_candles.close as candle_close,
      five_min_candles.high as candle_high,
      five_min_candles.low as candle_low,
      five_min_candles.open as candle_open,
      five_min_candles.symbol as candle_symbol
    from
      five_min_predictions
      join five_min_candles on five_min_candles.id = five_min_predictions.five_min_candle_id
    where
      five_min_predictions.symbol = %s
      and (to_timestamp(%f) - five_min_predictions.inserted_at) <= '%i seconds'::interval
  )";

  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, this->symbol.c_str(), this->symbol.size());

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol) +
                         std::to_string(ref_epoch).size() +
                         std::to_string(this->EXIRATION_SECONDS).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbol, ref_epoch,
           this->EXIRATION_SECONDS);

  PQfreemem(sanitized_symbol);

  const query_result_t result = this->conn.exec(query, debug);

  return result_to_predictions(result);
}

#endif
