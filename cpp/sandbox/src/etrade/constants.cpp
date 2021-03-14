#if !defined ETRADE__constants
#define ETRADE__constants

namespace ETrade {
namespace constants {
const char *ORDER_ACTIONS[4] = {
    "BUY",
    "BUY_TO_COVER",
    "SELL",
    "SELL_SHORT",
};

const char *ORDER_STATUSES[6] = {
    "CANCELLED", "CANCEL_REQUESTED", "EXECUTED", "OPEN", "PARTIAL", "PENDING",
};

const char *ORDER_TYPES[3] = {
    "LIMIT",
    "MARKET",
    "STOP_LIMIT",
};

} // namespace constants
} // namespace ETrade

#endif
