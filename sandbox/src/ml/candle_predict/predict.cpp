#ifndef ML__CANDLE_PREDICT_predict
#define ML__CANDLE_PREDICT_predict

#include "candle_predict.h" // ML::CandlePredict
#include "lib/utils/io.cpp" // ::utils::io
#include <stdio.h>          // snprintf
#include <string.h>         // strlen

void ML::CandlePredict::predict(const double ref_epoch) {
  this->db_candle.build();

  const char *cmd_format =
      "%s/bin/ml/candle_predict predict %s --duration-min=%i --env=%s "
      "--ref-epoch=%f --scope=%s --timestamps=%f > /dev/null 2>&1";

  const size_t cmd_l =
      strlen(cmd_format) + strlen(APP_DIR) + this->symbol.size() +
      std::to_string(this->duration_minutes).size() + this->db_env.size() +
      2 * std::to_string(ref_epoch).size() +
      this->config.prediction_scope.size();

  char cmd[cmd_l];

  snprintf(cmd, cmd_l, cmd_format, APP_DIR, this->symbol.c_str(),
           this->duration_minutes, this->db_env.c_str(), ref_epoch,
           this->config.prediction_scope.c_str(), ref_epoch);

  ::utils::io::system_exec(cmd);
}

#endif
