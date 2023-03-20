#include "client/client.cpp"   // Alpaca::Client
#include "lib/formatted.cpp"   // Formatted
#include "lib/pg/pg.cpp"       // Pg
#include "lib/utils/io.cpp"    // utils::io
#include "quote/quote.cpp"     // Alpaca::Quote
#include "returns.cpp"         // Alpaca::Returns
#include "sessions.cpp"        // Alpaca::Sessions
#include "tao_bot/tao_bot.cpp" // Alpaca::TaoBot
#include <iostream>            // std::cout, std::endl
#include <list>                // std::list
#include <map>                 // std::map
#include <regex>               // std::regex
#include <sstream>             // std::ostringstream
#include <stdio.h>             // printf
#include <string>              // std::string
#include <vector>              // std::vector

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"cancel_orders <ORDER_IDS>    ", "Cancel outsanding orders"},
      {"fetch_quote <SYMBOL>         ", "Get quote for the given symbol"},
      {"log_returns                  ", "Print cumulative return"},
      {"log_sessions                 ",
       "Print account performance for recorded sessions"},
      {"quotes_stream <SYMBOLS>      ", "Stream quotes for given symbol(s)"},
      {"quotes_watch <SYMBOLS>       ",
       "Persist and make computations for fetched/streamed quotes"},
      {"stream_account               ", "Stream account info"},
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

  if (command == "log_sessions") {
    Alpaca::Sessions::log();
    exit(0);
  }

  if (command == "quotes_stream") {
    if (argc < 3) {
      std::string message = Formatted::error_message(
          "Please provide at least one symbol to stream.");

      throw std::invalid_argument(message);
    }

    Alpaca::Quote streamer;
    streamer.stream(argc, argv);

    exit(0);
  }

  if (command == "quotes_watch") {
    if (argc < 3) {
      std::string message = Formatted::error_message(
          "Please provide at least one symbol to stream.");

      throw std::invalid_argument(message);
    }

    std::list<std::string> args =
        ::utils::io::extract_args(argc, argv, ::utils::string::upcase);

    std::list<std::string>::iterator symbols_start = args.begin();
    symbols_start++;
    std::vector<std::string> symbols(symbols_start, args.end());

    Pg pg;
    pg.connect();

    Alpaca::Quote watcher(pg);
    watcher.watch(symbols);

    exit(0);
  }

  if (command == "stream_account") {
    std::map<std::string, std::string> flags =
        ::utils::io::extract_flags(argc, argv);

    Alpaca::Client alpaca_client(flags);
    alpaca_client.stream_account();

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
