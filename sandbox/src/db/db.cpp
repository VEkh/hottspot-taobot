#include "db/candle/candle.cpp"                     // DB::Candle
#include "db/historical_quote/historical_quote.cpp" // DB::HistoricalQuote
#include "db/position/position.cpp"                 // DB::Position
#include "db/quote/quote.cpp"                       // DB::Quote
#include "lib/formatted.cpp"                        // Formatted
#include "lib/pg/pg.cpp"                            // Pg
#include "lib/utils/io.cpp"                         // ::utils::io
#include <iostream>                                 // std::cout, std::endl
#include <list>                                     // std::list
#include <map>                                      // std::map
#include <sstream>                                  // std::ostringstream
#include <stdexcept>                                // std::invalid_argument
#include <stdio.h>                                  // printf
#include <string>                                   // std::string, std::stoi

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"build_candles                          <SYMBOL> <OPTS>",
       "Build five minute candles for the given symbol"},
      {"import_historical_quotes               <SYMBOL> <OPTS>",
       "Import symbol's historical quotes"},
      {"net_return                             <SYMBOL> <OPTS>",
       "Compute symbol's net return"},
      {"quote:upsert_all_avg_one_sec_variances <SYMBOL> <OPTS> ",
       "Retroactively upsert a symbol's average one second variances"},
  };

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::ostringstream message;

  message << fmt.bold << fmt.cyan << "Data CLI Usage:" << std::endl;

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

  if (command == "build_candles") {
    if (upcased_args.empty()) {
      std::string message =
          Formatted::error_message("Please provide at least one symbol.");

      throw std::invalid_argument(message);
    }

    if (flags["duration-min"].empty()) {
      std::string message = Formatted::error_message(
          "Please provide duration minutes with the --duration-min flag.");

      throw std::invalid_argument(message);
    }

    Pg pg(flags);
    pg.connect();

    DB::Candle candle(pg, std::stoi(flags["duration-min"]),
                      upcased_args.front());

    candle.build();

    pg.disconnect();

    exit(0);
  }

  if (command == "import_historical_quotes") {
    if (upcased_args.empty()) {
      std::string message =
          Formatted::error_message("Please provide at least one symbol.");

      throw std::invalid_argument(message);
    }

    Pg pg(flags);
    pg.connect();

    std::map<std::string, std::string> default_flags = {
        {"batch", "10000"},
    };

    flags = ::utils::map::merge(default_flags, flags);

    DB::HistoricalQuote db_historical_quote({
        .batch = flags["batch"],
        .conn = pg,
        .end_at = flags["end-at"],
        .start_at = flags["start-at"],
        .symbol = upcased_args.front(),
    });

    db_historical_quote.download();

    pg.disconnect();

    exit(0);
  }

  if (command == "net_return") {
    if (upcased_args.empty()) {
      std::string message =
          Formatted::error_message("Please provide at least one symbol.");

      throw std::invalid_argument(message);
    }

    std::map<std::string, std::string> default_flags = {
        {"end-at", ""},
        {"limit", "0"},
        {"project", "alpaca"},
        {"start-at", ""},
    };

    flags = ::utils::map::merge(default_flags, flags);

    Pg pg(flags);
    pg.connect();

    DB::Position db_position(pg);
    db_position.net_return({
        .api_key = flags["api-key"],
        .debug = ::utils::io::flag_to_bool("debug", flags["debug"]),
        .end_at = flags["end-at"],
        .limit = std::stoi(flags["limit"]),
        .log_positions =
            ::utils::io::flag_to_bool("log-positions", flags["log-positions"]),
        .project = flags["project"],
        .start_at = flags["start-at"],
        .symbol = upcased_args.front(),
    });

    pg.disconnect();

    exit(0);
  }

  if (command == "quote:upsert_all_avg_one_sec_variances") {
    if (upcased_args.empty()) {
      std::string message =
          Formatted::error_message("Please provide at least one symbol.");

      throw std::invalid_argument(message);
    }

    Pg pg(flags);
    pg.connect();

    DB::Quote db_quote(pg);
    db_quote.upsert_all_avg_one_sec_variances({
        .end_at = flags["end-at"],
        .start_at = flags["start-at"],
        .symbol = upcased_args.front(),
    });

    pg.disconnect();

    exit(0);
  }

  std::cout << fmt.bold << fmt.red;
  printf("Unknown command <%s>. Please refer to usage👇🏾\n\n",
         command.c_str());
  std::cout << fmt.reset;

  print_usage();
  exit(127);
}
