#ifndef ETRADE__constants
#define ETRADE__constants

namespace ETrade {
namespace constants {
const char *ORDER_ACTIONS[] = {
    "BUY",
    "BUY_TO_COVER",
    "SELL",
    "SELL_SHORT",
};

const char *ORDER_STATUSES[] = {
    "CANCELLED", "CANCEL_REQUESTED", "EXECUTED", "OPEN", "PARTIAL", "PENDING",
};

const char *ORDER_TYPES[] = {
    "MARKET",
};

} // namespace constants
} // namespace ETrade

#endif
