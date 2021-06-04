#include "etrade/stock_bot/stock_bot.cpp"
#include <iostream>

int main() {
  ETrade::StockBot stock_bot((char *)"AMC", 1);
  stock_bot.fetch_quote();
  std::cout << stock_bot.compute_normalized_quantity() << std::endl;
}
