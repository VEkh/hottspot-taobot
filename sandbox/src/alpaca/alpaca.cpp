#include "client/client.cpp"                 // Alpaca::Client
#include "db/quote/quote.cpp"                // DB::Quote
#include "lib/formatted.cpp"                 // Formatted
#include "lib/performance/logger/logger.cpp" // Performance::Logger
#include "lib/pg/pg.cpp"                     // Pg
#include "lib/utils/io.cpp"                  // utils::io
#include "performance/logger/logger.cpp"     // Alpaca::Performance::Logger
#include "quote/quote.cpp"                   // Alpaca::Quote
#include "tao_bot/tao_bot.cpp"               // Alpaca::TaoBot
#include <iostream>                          // std::cout, std::endl
#include <list>                              // std::list
#include <map>                               // std::map
#include <sstream>                           // std::ostringstream
#include <stdexcept>                         // std::invalid_argument
#include <stdio.h>                           // printf
#include <string>                            // std::string

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"cancel_orders <ORDER_IDS>                     ",
       "Cancel outsanding orders"},
      {"fetch_asset <SYMBOL>                          ",
       "Get asset info for the given symbol"},
      {"fetch_quote <SYMBOL>                          ",
       "Get quote for the given symbol"},
      {"log_benchmark                                 ",
       "Print cumulative return and compare to benchmark indexes"},
      {"log_snapshots <FLAGS>                         ",
       "Print daily account performance for the given api key"},
      {"quotes_stream <SYMBOLS>                       ",
       "Stream quotes for given symbol(s)"},
      {"quotes_watch <SYMBOLS>                        ",
       "Persist and make computations for fetched/streamed quotes"},
      {"stream_account                                ", "Stream account info"},
      {"tao_bot <SYMBOL> <QUANTITY>                   ",
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

// TODO: Re-factor into Alpaca::Cli class
int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage();
    exit(1);
  }

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::string command = argv[1];

  std::list<std::string> args = ::utils::io::extract_args(argc, argv);
  args.pop_front(); // Remove command arg

  std::list<std::string> upcased_args =
      ::utils::io::extract_args(argc, argv, ::utils::string::upcase);
  upcased_args.pop_front(); // Remove command arg

  std::map<std::string, std::string> flags =
      ::utils::io::extract_flags(argc, argv);

  if (command == "cancel_orders") {
    if (args.empty()) {
      std::string message =
          Formatted::error_message("Please provide at least one order id.");

      throw std::invalid_argument(message);
    }

    Alpaca::Client api_client(flags);

    for (const std::string arg : args) {
      const std::string response = api_client.cancel_order(arg);

      std::cout << fmt.bold << fmt.yellow;
      printf("Cancel Response: %s", response.c_str());
      std::cout << fmt.reset << std::endl;

      if (response.empty()) {
        std::cout << fmt.bold << fmt.green;
        printf("👍🏾Successfully cancelled order: %s", arg.c_str());
        std::cout << fmt.reset << std::endl;
      }
    }

    exit(0);
  }

  if (command == "fetch_asset") {
    if (upcased_args.empty()) {
      std::string message = Formatted::error_message(
          "Please provide at least one symbol to fetch.");

      throw std::invalid_argument(message);
    }

    Alpaca::Client alpaca_client(flags);

    std::string quote = alpaca_client.fetch_asset(upcased_args.front());
    puts(quote.c_str());

    exit(0);
  }

  if (command == "fetch_quote") {
    if (upcased_args.empty()) {
      std::string message = Formatted::error_message(
          "Please provide at least one symbol to fetch.");

      throw std::invalid_argument(message);
    }

    Alpaca::Client alpaca_client(flags);

    std::string quote = alpaca_client.fetch_quote(upcased_args.front());
    puts(quote.c_str());

    exit(0);
  }

  if (command == "log_benchmark") {
    Alpaca::Performance::Logger logger;

    logger.log_benchmark();

    exit(0);
  }

  if (command == "log_snapshots") {
    Pg pg(flags);
    pg.connect();

    Performance::Logger logger(pg);

    logger.log_daily_snapshots(flags);

    pg.disconnect();

    exit(0);
  }

  if (command == "quotes_stream") {
    if (upcased_args.empty()) {
      std::string message = Formatted::error_message(
          "Please provide at least one symbol to stream.");

      throw std::invalid_argument(message);
    }

    Pg pg(flags);
    pg.connect();

    Alpaca::Quote streamer(pg, flags);
    streamer.stream(upcased_args);

    pg.disconnect();

    exit(0);
  }

  if (command == "quotes_watch") {
    if (upcased_args.empty()) {
      std::string message = Formatted::error_message(
          "Please provide at least one symbol to stream.");

      throw std::invalid_argument(message);
    }

    Pg pg(flags);
    pg.connect();

    Alpaca::Quote watcher(pg, flags);
    watcher.watch(upcased_args);

    pg.disconnect();

    exit(0);
  }

  if (command == "stream_account") {
    Alpaca::Client alpaca_client(flags);
    alpaca_client.stream_account();

    exit(0);
  }

  if (command == "tao_bot") {
    if (upcased_args.empty()) {
      std::string message = Formatted::error_message(
          "Please provide at least one symbol to trade.");

      throw std::invalid_argument(message);
    }

    Alpaca::TaoBot tao_bot(upcased_args.front(), flags);
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
