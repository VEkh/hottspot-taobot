#ifndef DB__QUOTE_insert_latest_avg_one_sec_variances
#define DB__QUOTE_insert_latest_avg_one_sec_variances

#include "quote.h" // DB::Quote, query_result_t

void DB::Quote::insert_latest_avg_one_sec_variances() {
  const char *query = "select insert_latest_avg_one_sec_variances() as result";

  this->conn.exec(query);
}

#endif
