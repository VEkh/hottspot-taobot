#ifndef ETRADE__STOCK_BOT_compute_normalized_quantity
#define ETRADE__STOCK_BOT_compute_normalized_quantity

#include "stock_bot.h" // ETrade::StockBot, quote_t
#include <math.h>

int ETrade::StockBot::compute_normalized_quantity() {
  if (!this->FLAG_NORMALIZE_QUANTITY) {
    return this->quantity_mulitiplier;
  }

  const double current_price = this->quotes.back().current_price;

  const std::string basis_quote_string =
      this->etrade_client.fetch_quote(this->NORMALIZE_QUANTITY_BASIS_SYMBOL);

  const quote_t basis_quote =
      this->etrade_client.parse_quote(basis_quote_string);

  const double basis_price = basis_quote.current_price;

  return this->quantity_mulitiplier * ceil(basis_price / current_price);
}

#endif
