#if !defined ETRADE__STOCK_BOT_set_profit
#define ETRADE__STOCK_BOT_set_profit

#include "stock_bot.h" // ETrade::StockBot, order_t, quotes

void ETrade::StockBot::set_profit(order_t *order) {
  const double current_price = quotes.back()["currentPrice"];
  double profit;
  double sma_profit;

  bool is_long_position = order->action == order_action_t::BUY;
  bool is_short_position = order->action == order_action_t::SELL_SHORT;

  if (is_long_position) {
    profit = current_price - order->execution_price;
    sma_profit = simple_moving_average - order->sma_execution_price;
  } else if (is_short_position) {
    profit = order->execution_price - current_price;
    sma_profit = order->sma_execution_price - simple_moving_average;
  }

  order->profit = profit;
  order->sma_profit = sma_profit;
}

void ETrade::StockBot::set_profit(order_t *close_order,
                                  const order_t *open_order) {
  double profit;
  double sma_profit;

  bool is_long_position = close_order->action == order_action_t::SELL;
  bool is_short_position = close_order->action == order_action_t::BUY_TO_COVER;

  if (is_long_position) {
    profit = close_order->execution_price - open_order->execution_price;
    sma_profit =
        close_order->sma_execution_price - open_order->sma_execution_price;
  } else if (is_short_position) {
    profit = open_order->execution_price - close_order->execution_price;
    sma_profit =
        open_order->sma_execution_price - close_order->sma_execution_price;
  }

  close_order->profit = profit;
  close_order->sma_profit = sma_profit;
}

#endif
