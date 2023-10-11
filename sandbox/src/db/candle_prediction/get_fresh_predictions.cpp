#ifndef DB__CANDLE_PREDICTION_get_fresh_predictions
#define DB__CANDLE_PREDICTION_get_fresh_predictions

#include "candle_prediction.h" // DB::CandlePrediction, prediction_t, query_result_t
#include "result_to_predictions.cpp" // result_to_predictions
#include <libpq-fe.h>                // PQescapeLiteral, PQfreemem
#include <list>                      // std::list
#include <stdio.h>                   // snprintf
#include <string.h>                  // strlen
#include <string>                    // std::to_string
#include <time.h>                    // time

std::list<DB::CandlePrediction::prediction_t>
DB::CandlePrediction::get_fresh_predictions(
    const double ref_epoch = time(nullptr), const bool debug = false) {
  ;

  const char *query_format = R"(
    select
      candle_predictions.*,
      candles.close as candle_close,
      extract(epoch from candle_predictions.candle_closed_at) as candle_closed_at_epoch,
      candles.high as candle_high,
      candles.low as candle_low,
      candles.open as candle_open,
      candles.symbol as candle_symbol
    from
      candle_predictions
      join candles on candles.id = candle_predictions.candle_id
        and candles.duration_minutes = %i
    where
      candle_predictions.symbol = %s
      and candle_predictions.candle_closed_at between date_trunc('day', to_timestamp(%f))
      and to_timestamp(%f)
    order by
      candle_predictions.candle_closed_at desc,
      candle_predictions.model_name asc
  )";

  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, this->symbol.c_str(), this->symbol.size());

  const size_t query_l =
      strlen(query_format) + std::to_string(this->duration_minutes).size() +
      strlen(sanitized_symbol) + 2 * std::to_string(ref_epoch).size();

  char query[query_l];

  snprintf(query, query_l, query_format, this->duration_minutes,
           sanitized_symbol, ref_epoch, ref_epoch);

  PQfreemem(sanitized_symbol);

  const query_result_t result = this->conn.exec(query, debug);

  return result_to_predictions(result);
}

#endif
