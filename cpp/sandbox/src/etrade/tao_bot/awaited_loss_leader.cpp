#ifndef ETRADE__TAO_BOT_awaited_loss_leader
#define ETRADE__TAO_BOT_awaited_loss_leader

#include "get_loss_leader.cpp" // get_loss_leader
#include "tao_bot.h"           // ETrade::TaoBot
#include <iostream>            // std::cout, std::endl
#include <stdio.h>             // printf
#include <string>              // std::string
#include <unistd.h>            // usleep

bool ETrade::TaoBot::awaited_loss_leader() {
  const std::string loss_leader = get_loss_leader();

  if (this->open_order_ptr) {
    return false;
  }

  if (loss_leader.empty() || loss_leader == std::string(this->symbol)) {
    return false;
  }

  std::cout << fmt.bold << fmt.yellow;
  printf("😪 Awaiting loss leader");

  std::cout << fmt.reset << fmt.cyan;
  printf(" <%s> ", loss_leader.c_str());

  std::cout << fmt.bold << fmt.yellow;
  printf("to recover losses");

  std::cout << std::endl;

  usleep(this->POLLING_INTERVAL_SECONDS * 5e6);

  return true;
}

#endif
