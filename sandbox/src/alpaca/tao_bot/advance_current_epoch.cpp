#ifndef ALPACA__TAO_BOT_advance_current_epoch
#define ALPACA__TAO_BOT_advance_current_epoch

#include "tao_bot.h" // Alpaca::TaoBot, fmt
#include <iostream>  // std::cout, std::endl
#include <time.h>    // time
#include <unistd.h>  // usleep

void Alpaca::TaoBot::advance_current_epoch() {
  if (this->backtest.is_active) {
    advance_current_epoch(this->current_quote.timestamp);

    this->backtest.slow_query_countdown += 1;
    return;
  }

  usleep(5e5);

  advance_current_epoch(time(nullptr));
}

void Alpaca::TaoBot::advance_current_epoch(const double epoch) {
  if (this->backtest.should_await_epoch_advance(this->current_epoch, epoch)) {
    std::cout << fmt.bold << fmt.yellow;
    printf("😴 Awaiting epoch advance...");
    std::cout << fmt.reset << std::endl;

    usleep(5e5);

    return advance_current_epoch(epoch);
  }

  this->current_epoch = epoch;
}

#endif
