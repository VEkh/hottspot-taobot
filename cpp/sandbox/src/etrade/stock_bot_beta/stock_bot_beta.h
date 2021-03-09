#if !defined ETRADE__STOCK_BOT_BETA_H
#define ETRADE__STOCK_BOT_BETA_H

#include "lib/formatted.cpp" // Formatted

namespace ETrade {
class StockBotBeta {
public:
  void run();

  StockBotBeta(char *, int);

private:
  char *symbol;
  int quantity;

  Formatted::fmt_stream_t fmt = Formatted::stream();

  void initialize(char *, int);
  void log_start_message();
};
} // namespace ETrade

#endif
