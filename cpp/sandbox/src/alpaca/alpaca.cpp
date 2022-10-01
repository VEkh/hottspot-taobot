#include "client/client.cpp"   // Alpaca::Client
#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/io.cpp"    // utils::io
#include "returns.cpp"         // Alpaca::Returns
#include "tao_bot/tao_bot.cpp" // Alpaca::TaoBot
#include <iostream>            // std::cout, std::endl
#include <map>                 // std::map
#include <regex>               // std::regex
#include <sstream>             // std::ostringstream
#include <stdio.h>             // printf
#include <string>              // std::string

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"cancel_orders <ORDER_IDS>    ", "Cancel outsanding orders"},
      {"fetch_quote <SYMBOL>         ", "Get quote for the given symbol"},
      {"log_returns                  ", "Print cumulative return"},
      {"stream_account               ", "Stream account info"},
      {"stream_quotes <SYMBOLS>      ", "Stream quotes for given symbol(s)"},
      {"tao_bot <SYMBOL> <QUANTITY>  ",
       "Launch trading bot for the given currency pair"},
  };

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::ostringstream message;

  message << fmt.bold << fmt.cyan << "Alpaca Client Usage:" << std::endl;

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

  if (command == "analyze_momentum_reversals") {
    char *symbol = argc < 3 ? nullptr : argv[2];
    std::map<std::string, std::string> flags =
        ::utils::io::extract_flags(argc, argv);

    Alpaca::TaoBot tao_bot(symbol, flags);
    tao_bot.build_momentum_reversals();
    tao_bot.log_momentum_reversals();
    const bool should_buy = tao_bot.is_next_position_long();

    printf("Should buy next?: %i\n", should_buy);

    exit(0);
  }

  if (command == "cancel_orders") {
    std::map<std::string, std::string> flags =
        ::utils::io::extract_flags(argc, argv);

    Alpaca::Client api_client(flags);

    if (argc < 3) {
      std::string message =
          Formatted::error_message("Please provide at least one order id.");

      throw std::invalid_argument(message);
    }

    for (int i = 2; i < argc; i++) {
      std::string arg = argv[i];

      if (std::regex_search(arg, std::regex("^--.*"))) {
        continue;
      }

      const std::string response = api_client.cancel_order(arg);

      std::cout << fmt.bold << fmt.yellow;
      printf("Cancel Response: %s\n", response.c_str());
      std::cout << fmt.reset << std::endl;

      if (response.empty()) {
        std::cout << fmt.bold << fmt.green;
        printf("👍🏾Successfully cancelled order: %s\n", arg.c_str());
        std::cout << fmt.reset << std::endl;
      }
    }

    exit(0);
  }

  if (command == "fetch_quote") {
    Alpaca::Client alpaca_client;
    char *symbol = argc < 3 ? nullptr : argv[2];

    std::string quote = alpaca_client.fetch_quote(symbol);
    puts(quote.c_str());

    exit(0);
  }

  if (command == "log_returns") {
    Alpaca::Returns::log();

    exit(0);
  }

  if (command == "stream_account") {
    std::map<std::string, std::string> flags =
        ::utils::io::extract_flags(argc, argv);

    Alpaca::Client alpaca_client(flags);
    alpaca_client.stream_account();

    exit(0);
  }

  if (command == "stream_quotes") {
    if (argc < 3) {
      std::string message = Formatted::error_message(
          "Please provide at least one symbol to stream.");

      throw std::invalid_argument(message);
    }

    Alpaca::Client alpaca_client;
    alpaca_client.stream_quotes(argc, argv);

    exit(0);
  }

  if (command == "tao_bot") {
    char *symbol = argc < 3 ? nullptr : argv[2];
    std::map<std::string, std::string> flags =
        ::utils::io::extract_flags(argc, argv);

    Alpaca::TaoBot tao_bot(symbol, flags);
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
