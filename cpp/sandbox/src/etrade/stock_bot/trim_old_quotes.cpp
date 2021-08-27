#ifndef ETRADE__STOCK_BOT_trim_old_quotes
#define ETRADE__STOCK_BOT_trim_old_quotes

#include "stock_bot.h" // ETrade::StockBot, quote_t
#include <time.h>      // time_t, time
#include <vector>      // vector

void ETrade::StockBot::trim_old_quotes() {
  const int max_time_limit = 5 * 60;
  int i = 0;
  std::vector<quote_t>::iterator it = this->quotes.begin();
  time_t now;

  time(&now);

  while ((now - it->timestamp) > max_time_limit) {
    it++;
    i++;
  }

  if (!i) {
    return;
  }

  this->quotes.erase(this->quotes.begin(), this->quotes.begin() + i);
}

#endif
