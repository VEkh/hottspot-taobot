#ifndef OANDA__TAO_BOT_base_currency
#define OANDA__TAO_BOT_base_currency

#include "tao_bot.h" // Oanda::TaoBot
#include <string>    // std::string

/*
 * std::cmatch
 * std::regex
 * std::regex_constants
 * std::regex_search
 */
#include <regex>

std::string Oanda::TaoBot::base_currency() {
  std::cmatch match;
  std::regex_search(this->symbol, match, std::regex("^(\\w+)_\\w+$"));

  return match[1];
}

#endif
