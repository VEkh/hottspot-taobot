#ifndef ALPACA__TAO_BOT_awaited_loss_leader
#define ALPACA__TAO_BOT_awaited_loss_leader

#include "compute_martingale_quantity.cpp" // compute_martingale_quantity
#include "fetch_account_balance.cpp"       // fetch_account_balance
#include "get_loss_leader.cpp"             // get_loss_leader
#include "is_hedging.cpp"                  // is_hedging
#include "max_affordable_quantity.cpp"     // max_affordable_quantity
#include "read_sibling_performances.cpp"   // read_sibling_performances
#include "should_open_position.cpp"        // should_open_position
#include "tao_bot.h"                       // Alpaca::TaoBot, performance_t
#include <iostream>                        // std::cout, std::endl
#include <list>                            // std::list
#include <map>                             // std::map
#include <stdio.h>                         // printf
#include <string>                          // std::string
#include <unistd.h>                        // usleep

bool Alpaca::TaoBot::awaited_loss_leader() {
  if (is_hedging()) {
    return false;
  }

  if (!should_open_position()) {
    return false;
  }

  std::map<bool, const char *> bool_to_string = {
      {false, "No"},
      {true, "Yes"},
  };

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

  void (*loss_leader_waits)(Alpaca::TaoBot *) =
      [](Alpaca::TaoBot *self) -> void {
    std::cout << self->fmt.bold << self->fmt.yellow;
    puts("😪 I am the loss leader. Awaiting siblings to close.");
    std::cout << std::endl;

    self->performance = self->build_performance();
    self->write_performance();

    usleep(5e6);
  };

  std::list<performance_t> sibling_performances = read_sibling_performances();

  const performance_t sibling_loss_leader =
      get_loss_leader(sibling_performances);

  const bool is_sibling_open_ = is_sibling_open(sibling_performances);

  this->account_balance = fetch_account_balance(&this->api_client);

  const bool are_funds_sufficient =
      compute_martingale_quantity() < max_affordable_quantity();

  std::cout << fmt.bold << fmt.underline << fmt.yellow;
  printf("Me: ");
  std::cout << fmt.reset << fmt.cyan << fmt.underline;
  printf("<%s>\n", this->symbol);

  std::cout << fmt.reset << fmt.bold << fmt.yellow;
  printf("Deficit: %+'.2f • Funds Sufficient: %s\n",
         this->performance.current_loss_streak_balance,
         bool_to_string[are_funds_sufficient]);
  std::cout << fmt.reset << std::endl;

  std::cout << fmt.bold << fmt.underline << fmt.yellow;
  printf("Loss Leader: ");
  std::cout << fmt.reset << fmt.cyan << fmt.underline;
  printf("<%s>\n", sibling_loss_leader.symbol.c_str());

  std::cout << fmt.reset << fmt.bold << fmt.yellow;
  printf("Deficit: %+'.2f • Funds Sufficient: %s\n\n",
         sibling_loss_leader.current_loss_streak_balance,
         bool_to_string[sibling_loss_leader.are_funds_sufficient]);

  printf("Is sibling open? %s\n", bool_to_string[is_sibling_open_]);
  std::cout << fmt.reset << std::endl;

  if (sibling_loss_leader.symbol.empty()) {
    if (!this->performance.current_loss_streak_balance) {
      return false;
    }

    if (!are_funds_sufficient && is_sibling_open_) {
      loss_leader_waits(this);

      return true;
    }

    return false;
  }

  if (are_funds_sufficient && sibling_loss_leader.are_funds_sufficient &&
      sibling_loss_leader.is_position_open) {
    return false;
  }

  if (!are_funds_sufficient) {
    if (this->performance.current_loss_streak_balance <
        sibling_loss_leader.current_loss_streak_balance) {
      if (is_sibling_open_) {
        loss_leader_waits(this);
      }

      return is_sibling_open_;
    }
  }

  if (this->performance.current_loss_streak_balance <
      sibling_loss_leader.current_loss_streak_balance) {
    return false;
  }

  std::cout << fmt.bold << fmt.yellow;
  printf("😪 Awaiting loss leader");

  std::cout << fmt.reset << fmt.cyan;
  printf(" <%s> ", sibling_loss_leader.symbol.c_str());

  std::cout << fmt.bold << fmt.yellow;
  printf("to recover losses");

  std::cout << std::endl;

  usleep(5e6);

  return true;
}

#endif
