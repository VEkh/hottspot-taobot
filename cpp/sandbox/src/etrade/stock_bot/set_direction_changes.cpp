#if !defined ETRADE__STOCK_BOT_set_direction_changes
#define ETRADE__STOCK_BOT_set_direction_changes

#include "stock_bot.h" // ETrade::StockBot

void ETrade::StockBot::set_direction_changes() {
  if (!this->open_order_ptr) {
    return;
  }

  const double reverse_threshold = 1.1;

  if (!this->has_direction_reversed) {
    this->has_direction_reversed =
        (this->is_long_position &&
         long_average_sell_buy_ratio >= reverse_threshold) ||
        (!this->is_long_position &&
         long_average_buy_sell_ratio >= reverse_threshold);
  }

  if (!this->has_direction_returned && this->has_direction_reversed) {
    this->has_direction_returned =
        (this->is_long_position &&
         long_average_buy_sell_ratio >= reverse_threshold) ||
        (!this->is_long_position &&
         long_average_sell_buy_ratio >= reverse_threshold);
  }

  std::cout << fmt.bold << fmt.yellow;

  if (this->has_direction_returned) {
    std::cout << "👉🏾The position has returned." << std::endl;
  } else if (this->has_direction_reversed) {
    std::cout << "👈🏾The position has reversed." << std::endl;
  }

  std::cout << fmt.reset << std::endl;
}

#endif
