#ifndef ETRADE__TAO_BOT_fetch_account_balance
#define ETRADE__TAO_BOT_fetch_account_balance

#include "etrade/deps.cpp" // json
#include "tao_bot.h"       // ETrade::TaoBot

ETrade::TaoBot::account_balance_t ETrade::TaoBot::fetch_account_balance() {
  json account_balance_json =
      json::parse(this->etrade_client.fetch_account_balance());

  json computed_values = account_balance_json["BalanceResponse"]["Computed"];

  const double balance = computed_values["RealTimeValues"]["totalAccountValue"];
  const double day_trading_margin_buying_power =
      computed_values["dtMarginBuyingPower"];
  const double margin_buying_power = computed_values["dtMarginBuyingPower"];

  return {
      .balance = balance,
      .day_trading_margin_buying_power = day_trading_margin_buying_power,
      .margin_buying_power = margin_buying_power,
  };
}

#endif
