#if !defined ETRADE__types
#define ETRADE__types
namespace ETrade {
namespace t {
struct quote_t {
  double current_price;
  double high;
  double low;
  double simple_moving_average;
  char *symbol;
  long int timestamp;
};
} // namespace t
} // namespace ETrade
#endif
