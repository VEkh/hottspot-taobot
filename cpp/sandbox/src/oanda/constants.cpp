#ifndef OANDA__constants
#define OANDA__constants

namespace Oanda {
namespace constants {
const char *ORDER_ACTIONS[4] = {
    "BUY",
    "SELL",
};

const char *ORDER_STATUSES[6] = {
    "CANCELLED",
    "FILLED",
    "PENDING",
    "TRIGGERED",
};

const char *ORDER_TYPES[1] = {
    "MARKET",
};

} // namespace constants
} // namespace Oanda

#endif
