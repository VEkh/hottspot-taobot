#ifndef ETRADE__STOCK_BOT_fetch_account_balance
#define ETRADE__STOCK_BOT_fetch_account_balance

#include "etrade/deps.cpp" // json
#include "stock_bot.h"     // ETrade::StockBot

ETrade::StockBot::account_balance_t ETrade::StockBot::fetch_account_balance() {
  json account_balance_json =
      json::parse(this->etrade_client.fetch_account_balance());

  json computed_values = account_balance_json["BalanceResponse"]["Computed"];

  const double balance = computed_values["RealTimeValues"]["totalAccountValue"];
  const double day_trading_margin_buying_power =
      computed_values["dtMarginBuyingPower"];

  return {
      .balance = balance,
      .day_trading_margin_buying_power = day_trading_margin_buying_power,
  };
}

#endif
