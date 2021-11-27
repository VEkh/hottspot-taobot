#ifndef ETRADE__TAO_BOT_awaited_loss_leader
#define ETRADE__TAO_BOT_awaited_loss_leader

#include "compute_quantity.cpp"          // compute_quantity
#include "get_loss_leader.cpp"           // get_loss_leader
#include "max_affordable_quantity.cpp"   // max_affordable_quantity
#include "read_sibling_performances.cpp" // read_sibling_performances
#include "tao_bot.h"                     // ETrade::TaoBot
#include <iostream>                      // std::cout, std::endl
#include <stdio.h>                       // printf
#include <string>                        // std::string
#include <unistd.h>                      // usleep

bool ETrade::TaoBot::awaited_loss_leader() {
  if (this->open_order_ptr) {
    return false;
  }

  bool (*is_sibling_open)(std::list<performance_t> &) =
      [](std::list<performance_t> &sibling_performances) -> bool {
    std::list<performance_t>::iterator it = sibling_performances.begin();

    while (it != sibling_performances.end()) {
      if (it->is_position_open) {
        return true;
      }

      it++;
    }

    return false;
  };

  std::list<performance_t> sibling_performances = read_sibling_performances();

  const performance_t sibling_loss_leader =
      get_loss_leader(sibling_performances);

  const bool is_sibling_open_ = is_sibling_open(sibling_performances);
  const bool are_funds_sufficient =
      compute_quantity() < max_affordable_quantity();

  if (sibling_loss_leader.symbol.empty()) {
    if (!this->performance.current_loss_streak_balance) {
      return false;
    }

    if (!are_funds_sufficient && is_sibling_open_) {
      std::cout << fmt.bold << fmt.yellow;
      puts("😪 I am the loss leader. Awaiting siblings to close.");
      std::cout << std::endl;

      usleep(this->POLLING_INTERVAL_SECONDS * 5e6);

      return true;
    }

    return false;
  }

  if (are_funds_sufficient && sibling_loss_leader.are_funds_sufficient) {
    return false;
  }

  if (!are_funds_sufficient) {
    if (this->performance.current_loss_streak_balance <
        sibling_loss_leader.current_loss_streak_balance) {
      if (is_sibling_open_) {
        std::cout << fmt.bold << fmt.yellow;
        puts("😪 I am the loss leader. Awaiting siblings to close.");
        std::cout << std::endl;

        usleep(this->POLLING_INTERVAL_SECONDS * 5e6);
      }

      return is_sibling_open_;
    }
  }

  std::cout << fmt.bold << fmt.yellow;
  printf("Sibling loss leader: are_funds_sufficient: %i | Me: Are funds "
         "suffcient: %i\n",
         (int)sibling_loss_leader.are_funds_sufficient,
         (int)are_funds_sufficient);

  printf("😪 Awaiting loss leader");

  std::cout << fmt.reset << fmt.cyan;
  printf(" <%s> ", sibling_loss_leader.symbol.c_str());

  std::cout << fmt.bold << fmt.yellow;
  printf("to recover losses");

  std::cout << std::endl;

  usleep(this->POLLING_INTERVAL_SECONDS * 5e6);

  return true;
}

#endif
