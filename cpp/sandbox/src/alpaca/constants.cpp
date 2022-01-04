#ifndef ALPACA__constants
#define ALPACA__constants

namespace Alpaca {
namespace constants {
const char *ORDER_ACTIONS[] = {
    "BUY",
    "SELL",
};

const char *ORDER_STATUSES[] = {
    "CANCELLED", "FILLED", "INIT", "PENDING", "TRIGGERED",
};

const char *ORDER_TIMES_IN_FORCE[] = {
    "day",
};

const char *ORDER_TYPES[] = {
    "MARKET",
};

} // namespace constants
} // namespace Alpaca

#endif
