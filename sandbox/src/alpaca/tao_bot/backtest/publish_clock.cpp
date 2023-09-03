#ifndef ALPACA__TAO_BOT_BACKTEST_publish_clock
#define ALPACA__TAO_BOT_BACKTEST_publish_clock

#include "backtest.h"            // Alpaca::TaoBotBacktest
#include "pub_sub_clock_key.cpp" // pub_sub_clock_key
#include <string.h>              // snprintf, strlen
#include <string>                // std::string, std::to_string

void Alpaca::TaoBotBacktest::publish_clock(const double epoch,
                                           const bool debug = false) {
  const std::string key = pub_sub_clock_key();

  const char *query_format = "select pg_notify('%s', '%f')";

  const size_t query_l =
      strlen(query_format) + key.size() + std::to_string(epoch).size();

  char query[query_l];

  snprintf(query, query_l, query_format, key.c_str(), epoch);

  this->pg.exec(query, debug);
}

#endif
