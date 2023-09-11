#include "client/client.cpp"                 // Oanda::Client
#include "db/quote/quote.cpp"                // DB::Quote
#include "lib/formatted.cpp"                 // Formatted
#include "lib/performance/logger/logger.cpp" // Performance::Logger
#include "lib/pg/pg.cpp"                     // Pg
#include "lib/utils/io.cpp"                  // ::utils::io
#include "quote/quote.cpp"                   // Oanda::Quote
#include "tao_bot/tao_bot.cpp"               // Oanda::TaoBot
#include <iostream>                          // std::cout, std::endl
#include <list>                              // std::list
#include <map>                               // std::map
#include <sstream>                           // std::ostringstream
#include <stdio.h>                           // printf
#include <string>                            // std::string

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"fetch_quote <SYMBOL>                          ",
       "Get quote for the given symbol"},
      {"log_snapshots <FLAGS>                         ",
       "Print daily account performance for the given api key"},
      {"quotes_watch <SYMBOLS>                        ",
       "Persist and make computations for fetched/streamed quotes"},
      {"stream_account                                ", "Stream account info"},
      {"tao_bot <SYMBOL> <QUANTITY>                   ",
       "Launch trading bot for the given currency pair"},
  };

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::ostringstream message;

  message << fmt.bold << fmt.cyan << "Oanda Client Usage:" << std::endl;

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

  std::list<std::string> args = ::utils::io::extract_args(argc, argv);
  args.pop_front(); // Remove command arg

  std::list<std::string> upcased_args =
      ::utils::io::extract_args(argc, argv, ::utils::string::upcase);
  upcased_args.pop_front(); // Remove command arg

  std::map<std::string, std::string> flags =
      ::utils::io::extract_flags(argc, argv);

  if (command == "fetch_quote") {
    if (upcased_args.empty()) {
      std::string message = Formatted::error_message(
          "Please provide at least one symbol to trade.");

      throw std::invalid_argument(message);
    }

    const std::string symbol = upcased_args.front();
    Oanda::Client oanda_client(flags);

    std::string quote = oanda_client.fetch_quote(symbol);
    puts(quote.c_str());

    exit(0);
  }

  if (command == "log_snapshots") {
    Oanda::Client api_client(flags);

    Pg pg(flags);
    pg.connect();

    Performance::Logger logger(pg);

    logger.log_daily_snapshots({
        .api_key_id = api_client.config.account_id,
        .flags = flags,
    });

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

    Oanda::Quote watcher(pg, flags);
    watcher.watch(upcased_args);

    pg.disconnect();

    exit(0);
  }

  if (command == "stream_account") {
    Oanda::Client oanda_client(flags);
    oanda_client.stream_account();

    exit(0);
  }

  if (command == "tao_bot") {
    if (upcased_args.empty()) {
      std::string message = Formatted::error_message(
          "Please provide at least one symbol to trade.");

      throw std::invalid_argument(message);
    }

    const std::string symbol = upcased_args.front();

    Oanda::TaoBot tao_bot(symbol, flags);
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
