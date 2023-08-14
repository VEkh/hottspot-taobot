#ifndef OANDA__TAO_BOT_base_currency
#define OANDA__TAO_BOT_base_currency

#include "tao_bot.h" // Oanda::TaoBot
#include <string>    // std::string

/*
 * std::regex
 * std::regex_constants
 * std::regex_search
 * std::smatch
 */
#include <regex>

std::string Oanda::TaoBot::base_currency() {
  std::smatch match;
  std::regex_search(this->symbol, match, std::regex("^(\\w+)_\\w+$"));

  return match[1];
}

#endif
