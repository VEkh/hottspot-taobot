#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "position_target_movement.cpp" // position_target_movement
#include "secured_profit_ratio.cpp"     // secured_profit_ratio
#include "tao_bot.h"                    // Alpaca::TaoBot, fmt
#include <algorithm>                    // std::max std::min
#include <iostream>                     // std::cout, std::endl
#include <math.h>                       // INFINITY, abs
#include <stdio.h>                      // puts

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices(
    order_t *open_order_ptr_, const order_t *opposite_close_order_ptr = nullptr,
    const order_t *opposite_open_order_ptr = nullptr) {
  double max_loss = this->exit_prices.max_loss ? this->exit_prices.max_loss
                                               : -position_target_movement();

  double min_profit = INFINITY;
  double lower_secure_profit = INFINITY;
  double upper_secure_profit = INFINITY;

  if (opposite_close_order_ptr &&
      opposite_close_order_ptr->status == order_status_t::ORDER_FILLED &&
      opposite_close_order_ptr->profit) {
    if (!open_order_ptr_->max_profit_reset) {
      open_order_ptr_->max_profit_reset = true;
      this->exit_prices.upper_secure_profit = 0;
    }

    const double secured_profit_ratio_ = secured_profit_ratio(open_order_ptr_);
    // NOTE: Needs to be small enough to be attainable, but big enough to evade
    // natural corrections
    const double target_profit = 0.75 * position_target_movement();

    const double raw_min_profit =
        target_profit - opposite_close_order_ptr->profit;

    max_loss = -target_profit - opposite_close_order_ptr->profit;
    min_profit = raw_min_profit / secured_profit_ratio_;
    lower_secure_profit = min_profit * secured_profit_ratio_;
    upper_secure_profit =
        std::max(this->exit_prices.upper_secure_profit,
                 open_order_ptr_->max_profit * secured_profit_ratio_);

    std::cout << fmt.bold << fmt.yellow;
    printf("🚩 Awaiting hedge to close: { lower_secure_profit: %.2f, max_loss: "
           "%2.f, min_profit: %.2f, upper_secure_profit: %.2f }\n",
           lower_secure_profit, max_loss, min_profit, upper_secure_profit);
    std::cout << fmt.reset << std::endl;
  }

  return {
      .lower_secure_profit = lower_secure_profit,
      .max_loss = max_loss,
      .min_profit = min_profit,
      .upper_secure_profit = upper_secure_profit,
  };
}

// Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices(
//     order_t *open_order_ptr_, const order_t *opposite_close_order_ptr =
//     nullptr, const order_t *opposite_open_order_ptr = nullptr) {
//   const double secured_profit_ratio_ = secured_profit_ratio(open_order_ptr_);
//   const double winner_secure_profit_ratio = 0.7;

//   double max_loss = -INFINITY;
//   double min_profit =
//       this->exit_prices.min_profit
//           ? this->exit_prices.min_profit
//           : position_target_movement() / winner_secure_profit_ratio;

//   double lower_secure_profit = min_profit * winner_secure_profit_ratio;

//   double upper_secure_profit =
//       open_order_ptr_ == nullptr
//           ? 0
//           : std::max(this->exit_prices.upper_secure_profit,
//                      open_order_ptr_->max_profit *
//                      winner_secure_profit_ratio);

//   if (opposite_close_order_ptr && opposite_open_order_ptr &&
//       opposite_close_order_ptr->status == order_status_t::ORDER_FILLED &&
//       opposite_close_order_ptr->profit) {
//     if (!open_order_ptr_->max_profit_reset) {
//       open_order_ptr_->max_profit_reset = true;
//       open_order_ptr_->max_profit = open_order_ptr_->profit;
//       this->exit_prices.upper_secure_profit = open_order_ptr_->profit;
//     }

//     std::cout << fmt.bold << fmt.yellow;
//     puts("🚩 Awaiting hedge to close");
//     std::cout << fmt.reset << std::endl;

//     const double spread = abs(open_order_ptr_->execution_price -
//                               opposite_open_order_ptr->execution_price);

//     const double realized_profit =
//         open_order_ptr_->profit + opposite_close_order_ptr->profit;
//     const double target_profit = 0.75 * position_target_movement();

//     max_loss = -(opposite_close_order_ptr->profit + target_profit);

//     min_profit = -(opposite_close_order_ptr->profit -
//                    (target_profit / secured_profit_ratio_));
//     lower_secure_profit = -(opposite_close_order_ptr->profit -
//     target_profit); upper_secure_profit =
//         std::max(this->exit_prices.upper_secure_profit,
//                  (open_order_ptr_->max_profit -
//                   (realized_profit * (1 - secured_profit_ratio_))));
//   }

//   return {
//       .lower_secure_profit = lower_secure_profit,
//       .max_loss = max_loss,
//       .min_profit = min_profit,
//       .upper_secure_profit = upper_secure_profit,
//   };
// }

// Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices(
//     const order_t *open_order_ptr_,
//     const order_t *opposite_close_order_ptr = nullptr) {
//   double max_loss = this->exit_prices.max_loss ? this->exit_prices.max_loss
//                                                : -position_target_movement();

//   if (opposite_close_order_ptr &&
//       opposite_close_order_ptr->status == order_status_t::ORDER_FILLED) {
//     max_loss = std::min(max_loss, opposite_close_order_ptr->profit);
//   }

//   const double secured_profit_ratio_ = secured_profit_ratio(open_order_ptr_);

//   const double min_profit = abs(2 * max_loss) / secured_profit_ratio_;
//   const double lower_secure_profit = min_profit * secured_profit_ratio_;

//   const double upper_secure_profit =
//       open_order_ptr_ == nullptr
//           ? 0
//           : std::max(this->exit_prices.upper_secure_profit,
//                      open_order_ptr_->max_profit * secured_profit_ratio_);

//   return {
//       .lower_secure_profit = lower_secure_profit,
//       .max_loss = max_loss,
//       .min_profit = min_profit,
//       .upper_secure_profit = upper_secure_profit,
//   };
// }

#endif
