#ifndef ALPACA__constants
#define ALPACA__constants

namespace Alpaca {
namespace constants {
const char *ORDER_ACTIONS[] = {
    "BUY",
    "SELL",
};

const char *ORDER_STATUSES[] = {
    "canceled",         "done_for_day",   "expired",         "filled",   "new",
    "partially_filled", "pending_cancel", "pending_replace", "replaced",
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
