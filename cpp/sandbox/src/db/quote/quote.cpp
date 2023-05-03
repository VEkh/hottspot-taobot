#ifndef DB__QUOTE
#define DB__QUOTE

#include "quote.h"            // DB::Quote
#include "db/utils/utils.cpp" // DB::Utils
#include "lib/pg/pg.h"        // Pg

#include "get.cpp"
#include "get_last.cpp"
#include "get_one_sec_variance_avgs.cpp"
#include "get_stop_profit.cpp"
#include "upsert.cpp"
#include "watch_avg_one_sec_variances.cpp"

DB::Quote::Quote(Pg c) {
  this->conn = c;
  this->db_utils = DB::Utils(this->conn);

  this->db_utils.set_param({"statement_timeout", "10000"});
}

#endif
