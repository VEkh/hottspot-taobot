#ifndef OANDA__TAO_BOT_await_market_open
#define OANDA__TAO_BOT_await_market_open

#include "tao_bot.h" // Oanda::TaoBot, fmt
#include <chrono>    // std::chrono
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // puts
#include <thread>    // std::this_thread

void Oanda::TaoBot::await_market_open() {
  std::cout << fmt.yellow << fmt.bold;
  puts("Waiting for the market to open 😴");
  std::cout << fmt.reset;

  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}

#endif
