#ifndef OANDA__TAO_BOT_get_real_time_quote
#define OANDA__TAO_BOT_get_real_time_quote

#include "tao_bot.h" // Oanda::TaoBot, quote_t
#include <iostream>  // std::cout
#include <list>      // std::list
#include <regex>     // std::regex, std::regex_constants, std::regex_search
#include <stdio.h>   // printf
#include <string>    // std::string

Oanda::TaoBot::quote_t
Oanda::TaoBot::get_real_time_quote(const std::string symbol_) {
  if (this->backtest.is_active) {
    const std::list<quote_t> quotes_ = this->quoter.db_quote.get_last({
        .debug = this->api_client.config.debug_sql,
        .end_at = this->current_epoch,
        .limit = 1,
        .sort_direction = "desc",
        .start_at = this->current_epoch - 5,
        .symbol = symbol_,
    });

    return quotes_.empty() ? quote_t() : quotes_.front();
  }

  const std::string quote_response = this->api_client.fetch_quote(symbol_);

  if (std::regex_search(
          quote_response,
          std::regex("invalid value specified", std::regex_constants::icase))) {

    std::cout << fmt.bold << fmt.red;
    printf("[OANDA__TAO_BOT_get_real_time_quote]: ❗%s quote isn't available.\n",
           symbol_.c_str());
    std::cout << fmt.reset;

    return quote_t();
  }

  return this->api_client.parse_quote(quote_response);
}

#endif
