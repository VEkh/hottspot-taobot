#include "client/client.cpp"               // ETrade::Client
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include "lib/utils/io.cpp"                // utils::io
#include "returns.cpp"                     // ETrade::Returns
#include "tao_bot/tao_bot.cpp"             // ETrade::TaoBot
#include <iostream>                        // std::cout, std::endl
#include <map>                             // std::map
#include <sstream>                         // std::ostringstream
#include <stdexcept>                       // std::invalid_argument
#include <stdio.h>                         // printf
#include <stdlib.h>                        // strtol
#include <string.h>                        // strcmp
#include <string>                          // std::string

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"cancel_orders <ORDER_IDS>    ", "Cancel outsanding orders"},
      {"fetch <URL>                  ", "Generic authorized request"},
      {"fetch_access_token           ",
       "Get authorization token (modes: --auto | --manual)"},
      {"fetch_account_snapshot        ", "Get current account balance"},
      {"fetch_quote <SYMBOL>         ", "Get quote for the given symbol"},
      {"log_returns                  ", "Print cumulative return"},
      {"refresh_token                ", "Refresh authorization tokens"},
      {"tao_bot <SYMBOL> <QUANTITY>",
       "Launch trading bot for the given symbol"},
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
    ETrade::Client api_client;

    if (argc < 3) {
      std::string message =
          Formatted::error_message("Please provide at least one order id.");

      throw std::invalid_argument(message);
    }

    for (int i = 2; i < argc; i++) {
      int order_id = strtol(argv[i], nullptr, 10);

      CurlClient curl_client = api_client.cancel_order(order_id);
      std::cout << curl_client.response.body << std::endl;
    }

    exit(0);
  }

  if (command == "fetch") {
    ETrade::Client api_client;
    char *url = argc < 3 ? nullptr : argv[2];

    CurlClient curl_client = api_client.fetch(url);
    std::cout << curl_client.response.body << std::endl;

    exit(0);
  }

  if (command == "fetch_access_token") {
    const char *mode = argc < 3 ? "--auto" : argv[2];
    ETrade::Client api_client;

    if (!strcmp(mode, "--auto")) {
      api_client.fetch_access_token();
    } else if (!strcmp(mode, "--manual")) {
      api_client.manual_fetch_access_token();
    } else {
      std::string message = Formatted::error_message(
          "Please provide a valid option: --auto | --manual");

      throw std::invalid_argument(message);
    }

    exit(0);
  }

  if (command == "fetch_account_snapshot") {
    ETrade::Client api_client;
    std::cout << api_client.fetch_account_snapshot() << std::endl;

    exit(0);
  }

  if (command == "fetch_quote") {
    ETrade::Client api_client;
    char *symbol = argc < 3 ? nullptr : argv[2];

    std::string quote = api_client.fetch_quote(symbol);
    std::cout << quote;

    exit(0);
  }

  if (command == "log_returns") {
    ETrade::Returns::log();

    exit(0);
  }

  if (command == "refresh_token") {
    ETrade::Client api_client;
    api_client.refresh_token();

    exit(0);
  }

  if (command == "tao_bot") {
    char *symbol = argc < 3 ? nullptr : argv[2];
    int quantity = argc < 4 ? 0 : strtol(argv[3], nullptr, 10);
    std::map<std::string, std::string> flags =
        ::utils::io::extract_flags(argc, argv);

    ETrade::TaoBot tao_bot(symbol, quantity, flags);
    tao_bot.run();

    exit(0);
  }

  std::cout << fmt.bold << fmt.red;
  printf("Unknown command <%s>. Please refer to usage👇🏾\n\n",
         command.c_str());
  std::cout << fmt.reset;

  print_usage();
  exit(127);
}
