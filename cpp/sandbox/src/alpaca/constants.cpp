#ifndef ALPACA__constants
#define ALPACA__constants

namespace Alpaca {
namespace constants {
const char *ORDER_ACTIONS[] = {
    "buy",
    "sell",
};

const char *ORDER_STATUSES[] = {
    "accepted",
    "canceled",
    "done_for_day",
    "expired",
    "filled",
    "init",
    "new",
    "partially_filled",
    "pending_cancel",
    "pending_replace",
    "replaced",
};

const char *ORDER_TIMES_IN_FORCE[] = {
    "day",
};

const char *ORDER_TYPES[] = {
    "limit",
    "market",
};

} // namespace constants
} // namespace Alpaca

#endif
