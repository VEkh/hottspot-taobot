#ifndef ML__FIVE_MIN_PREDICT_predict
#define ML__FIVE_MIN_PREDICT_predict

#include "five_min_predict.h" // ML::FiveMinPredict
#include "lib/utils/io.cpp"   // ::utils::io
#include <stdio.h>            // snprintf
#include <string.h>           // strlen

void ML::FiveMinPredict::predict(const double ref_epoch) {
  this->db_candle.build();

  const char *cmd_format = "%s/bin/ml/five_min_predict predict %s --env=%s "
                           "--ref-epoch=%f --timestamps=%f > /dev/null 2>&1";

  const size_t cmd_l = strlen(cmd_format) + strlen(APP_DIR) +
                       this->symbol.size() + this->db_env.size() +
                       2 * std::to_string(ref_epoch).size();

  char cmd[cmd_l];

  snprintf(cmd, cmd_l, cmd_format, APP_DIR, this->symbol.c_str(),
           this->db_env.c_str(), ref_epoch, ref_epoch);

  ::utils::io::system_exec(cmd);
}

#endif
