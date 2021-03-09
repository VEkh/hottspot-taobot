#include "client/client.cpp"                 // ETrade::Client
#include "lib/curl_client/curl_client.cpp"   // CurlClient
#include "lib/formatted.cpp"                 // Formatted
#include "lib/utils/debug.cpp"               // utils::debug
#include "stock_bot/stock_bot.cpp"           // ETrade::StockBot
#include "stock_bot_beta/stock_bot_beta.cpp" // ETrade::StockBotBeta
#include <iostream>                          // std::cout, std::endl
#include <map>                               // std::map
#include <sstream>                           // std::ostringstream
#include <stdexcept>                         // std::invalid_argument
#include <stdlib.h>                          // strtol
#include <string>                            // std::string

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"cancel_orders <ORDER_IDS>   ", "Cancel outsanding orders"},
      {"fetch <URL>                 ", "Generic authorized request"},
      {"fetch_access_token          ", "Get authorization token"},
      {"fetch_quote <SYMBOL>        ", "Get quote for the given symbol"},
      {"refresh_token               ", "Refresh authorization tokens"},
      {"stock_bot <SYMBOL> <QUANTITY>",
       "Launch trading bot for the given symbol"},
      {"stock_bot_beta <SYMBOL> <QUANTITY>",
       "Launch (beta) trading bot for the given symbol"},
  };

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::ostringstream message;

  message << fmt.bold << fmt.cyan << "E*TRADE Client Usage:" << std::endl;

  std::map<std::string, const char *>::iterator it;
  for (it = commands.begin(); it != commands.end(); ++it) {
    message << fmt.bold << fmt.yellow << it->first << fmt.reset << " | "
            << it->second << std::endl;
  }

  std::cout << message.str();
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage();
    exit(1);
  }

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::string command = argv[1];

  if (command == "cancel_orders") {
    ETrade::Client etrade_client;

    if (argc < 3) {
      std::string message =
          Formatted::error_message("Please provide at least one order id.");

      throw std::invalid_argument(message);
    }

    for (int i = 2; i < argc; i++) {
      int order_id = strtol(argv[i], nullptr, 10);

      CurlClient curl_client = etrade_client.cancel_order(order_id);
      std::cout << curl_client.response.body << std::endl;
    }

    exit(0);
  }

  if (command == "fetch") {
    ETrade::Client etrade_client;
    char *url = argc < 3 ? nullptr : argv[2];

    CurlClient curl_client = etrade_client.fetch(url);
    std::cout << curl_client.response.body << std::endl;

    exit(0);
  }

  if (command == "fetch_access_token") {
    ETrade::Client etrade_client;
    etrade_client.fetch_access_token();

    exit(0);
  }

  if (command == "fetch_quote") {
    ETrade::Client etrade_client;
    char *symbol = argc < 3 ? nullptr : argv[2];

    std::string quote = etrade_client.fetch_quote(symbol);
    std::cout << quote;

    exit(0);
  }

  if (command == "refresh_token") {
    ETrade::Client etrade_client;
    etrade_client.refresh_token();

    exit(0);
  }

  if (command == "stock_bot") {
    char *symbol = argc < 3 ? nullptr : argv[2];
    int quantity = argc < 4 ? 0 : strtol(argv[3], nullptr, 10);
    char *action = argc < 5 ? nullptr : argv[4];

    while (true) {
      ETrade::StockBot stock_bot(symbol, quantity, action);
      stock_bot.run();

      action = stock_bot.next_order_action;
      const char *action_text = action ? action : "NEUTRAL";

      std::cout << fmt.bold << fmt.blue;
      std::cout << "\n🔃 Finished stradding. Re-running with " << action_text
                << "\n"
                << std::endl;
      std::cout << fmt.reset << fmt.blue;
    }

    exit(0);
  }

  if (command == "stock_bot_beta") {
    char *symbol = argc < 3 ? nullptr : argv[2];
    int quantity = argc < 4 ? 0 : strtol(argv[3], nullptr, 10);

    ETrade::StockBotBeta stock_bot_beta(symbol, quantity);
    stock_bot_beta.run();

    exit(0);
  }

  std::cout << fmt.bold << fmt.red << "Unknown command <" << command
            << ">. Please refer to usage👇🏾\n"
            << fmt.reset << std::endl;

  print_usage();
  exit(127);
}
