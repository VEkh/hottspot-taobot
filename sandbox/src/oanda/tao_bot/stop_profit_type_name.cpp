#ifndef OANDA__TAO_BOT_stop_profit_type_name
#define OANDA__TAO_BOT_stop_profit_type_name

#include "stop_profit_type.cpp" // stop_profit_type
#include "tao_bot.h"            // Oanda::TaoBot, stop_profit_type_t
#include <string>               // std::string

std::string Oanda::TaoBot::stop_profit_type_name(const order_t *order) {
  const stop_profit_type_t type = stop_profit_type(order);

  switch (type) {
  case stop_profit_type_t::STOP_PROFIT_CROSS_RANGE: {
    return "STOP_PROFIT_CROSS_RANGE";
  }
  case stop_profit_type_t::STOP_PROFIT_EXTEND_RANGE: {
    return "STOP_PROFIT_CROSS_RANGE";
  }
  default: {
    return "STOP_PROFIT_NULL";
  }
  }
}

#endif