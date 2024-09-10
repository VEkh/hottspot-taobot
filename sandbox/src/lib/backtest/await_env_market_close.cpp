#ifndef BACKTEST_await_env_market_close
#define BACKTEST_await_env_market_close

#include "backtest.h"                        // Alpaca::TaoBotBacktest, fmt
#include "should_await_env_market_close.cpp" // should_await_env_market_close
#include <iostream>                          // std::cout, std::endl

void Backtest::await_env_market_close(const double market_close_epoch,
                                      const double next_market_open_epoch) {
  if (!should_await_env_market_close(market_close_epoch,
                                     next_market_open_epoch)) {
    return;
  }

  std::cout << fmt.bold << fmt.yellow;
  printf("😴 Awaiting environment market close...");
  std::cout << fmt.reset << std::endl;

  usleep(5e5);

  return await_env_market_close(market_close_epoch, next_market_open_epoch);
}

#endif
