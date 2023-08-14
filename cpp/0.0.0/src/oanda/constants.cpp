#ifndef OANDA__constants
#define OANDA__constants

namespace Oanda {
namespace constants {
const char *ORDER_ACTIONS[] = {
    "BUY",
    "SELL",
};

const char *ORDER_STATUSES[] = {
    "CANCELLED", "FILLED", "INIT", "PENDING", "TRIGGERED",
};

const char *ORDER_TIMES_IN_FORCE[] = {
    "FOK",
    "GTC",
};

const char *ORDER_TYPES[] = {
    "LIMIT",
    "MARKET",
};

const char *TRADE_STATUSES[] = {
    "CLOSED",
    "OPEN",
};

} // namespace constants
} // namespace Oanda

#endif
