#ifndef ML__FIVE_MIN_PREDICT_predict
#define ML__FIVE_MIN_PREDICT_predict

#include "five_min_predict.h" // ML::FiveMinPredict
#include "lib/utils/io.cpp"   // ::utils::io
#include <libpq-fe.h>         // PQescapeLiteral, PQfreemem
#include <stdio.h>            // snprintf
#include <string.h>           // strlen

void ML::FiveMinPredict::predict(const double ref_epoch) {
  // TODO: Make timestamps value 'now()' in non-backtest mode
  const char *cmd_format = "%s/bin/ml/five_min_predict predict %s --env=%s "
                           "--ref-epoch=%f --timestamps=%f > /dev/null 2>&1";
  const std::string db_env = this->conn.flags["env"];

  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, this->symbol.c_str(), this->symbol.size());

  const size_t cmd_l = strlen(cmd_format) + strlen(APP_DIR) +
                       strlen(sanitized_symbol) + db_env.size() +
                       2 * std::to_string(ref_epoch).size();

  char cmd[cmd_l];

  snprintf(cmd, cmd_l, cmd_format, APP_DIR, sanitized_symbol, db_env.c_str(),
           ref_epoch, ref_epoch);

  PQfreemem(sanitized_symbol);

  ::utils::io::system_exec(cmd);
}

#endif
