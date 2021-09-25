#ifndef ETRADE__TAO_BOT_await_market_open
#define ETRADE__TAO_BOT_await_market_open

#include "tao_bot.h" // ETrade::TaoBot, fmt
#include <chrono>      // std::chrono
#include <iostream>    // std::cout, std::endl
#include <stdio.h>     // puts
#include <thread>      // std::this_thread

void ETrade::TaoBot::await_market_open() {
  std::cout << fmt.yellow << fmt.bold;
  puts("Waiting for the market to open 😴");
  std::cout << fmt.reset;

  this->api_client.refresh_token();

  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}

#endif
