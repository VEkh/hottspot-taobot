#ifndef ALPACA__TAO_BOT_await_market_open
#define ALPACA__TAO_BOT_await_market_open

#include "tao_bot.h" // Alpaca::TaoBot, fmt
#include <iostream>  // std::cout, std::endl, std::flush
#include <stdio.h>   // puts
#include <unistd.h>  // usleep

void Alpaca::TaoBot::await_market_open() {
  std::cout << fmt.yellow << fmt.bold;
  puts("Waiting for the market to open 😴");
  std::cout << fmt.reset << std::flush;

  usleep(3 * 1e6);
}

#endif
