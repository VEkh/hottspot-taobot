#ifndef ETRADE__STOCK_BOT_await_market_open
#define ETRADE__STOCK_BOT_await_market_open

#include "stock_bot.h" // ETrade::StockBot, fmt
#include <chrono>      // std::chrono
#include <iostream>    // std::cout, std::endl
#include <stdio.h>     // puts
#include <thread>      // std::this_thread

void ETrade::StockBot::await_market_open() {
  std::cout << fmt.yellow << fmt.bold;
  puts("Waiting for the market to open 😴");
  std::cout << fmt.reset;

  this->etrade_client.refresh_token();

  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}

#endif
