#ifndef ALPACA__TAO_BOT_BACKTEST_pub_sub_clock_key
#define ALPACA__TAO_BOT_BACKTEST_pub_sub_clock_key

#include "backtest.h" // Alpaca::TaoBotBacktest
#include <string>     // std::string

std::string Alpaca::TaoBotBacktest::pub_sub_clock_key() {
  return this->config.api_key_id + "-clock";
}

#endif
