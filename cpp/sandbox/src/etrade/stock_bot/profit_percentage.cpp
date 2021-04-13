#if !defined ETRADE__STOCK_BOT_profit_percentage
#define ETRADE__STOCK_BOT_profit_percentage

#include "stock_bot.h" // ETrade::StockBot, order_t

double ETrade::StockBot::profit_percentage(const order_t *order_ptr) {
  if (!order_ptr) {
    return 0.0;
  }

  if (!order_ptr->execution_price) {
    return 0.0;
  }

  return 100 * (order_ptr->profit / order_ptr->execution_price);
}

#endif
