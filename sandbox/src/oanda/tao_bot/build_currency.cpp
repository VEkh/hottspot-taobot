#ifndef OANDA__TAO_BOT_build_currency
#define OANDA__TAO_BOT_build_currency

#include "tao_bot.h" // Oanda::TaoBot
#include <regex>     // std::regex, std::regex_search, std::smatch

void Oanda::TaoBot::build_currency() {
  std::smatch match;
  std::regex_search(this->symbol, match, std::regex("^(\\w+)_(\\w+)$"));

  std::smatch::iterator it;

  this->currency = {
      .base = match[1],
      .quote = match[2],
  };
}

#endif
