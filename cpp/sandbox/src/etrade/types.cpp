#if !defined ETRADE__types
#define ETRADE__types

#include <utility> // std::pair

namespace ETrade {
namespace t {
struct quote_t {
  double current_price;
  double high;
  double low;
  std::pair<int, double> simple_moving_average;
  char *symbol;
  long int timestamp;
};
} // namespace t
} // namespace ETrade
#endif
