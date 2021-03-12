#if !defined ETRADE__types
#define ETRADE__types

#include <utility> // std::pair

namespace ETrade {
namespace t {
struct sma_t {
  double buy_delta = 0.00;
  double price;
  int seconds = 0;
  double sell_delta = 0.00;
};

struct quote_t {
  double current_price;
  double high;
  double low;
  sma_t simple_moving_average;
  char *symbol;
  long int timestamp;
};
} // namespace t
} // namespace ETrade
#endif
