#include "db/candle/candle.cpp"                  // DB::Candle
#include "db/historical_quote/alpaca/alpaca.cpp" // DB::HistoricalQuote::Alpaca
#include "db/historical_quote/base/base.cpp"     // DB::HistoricalQuote::Base
#include "db/historical_quote/oanda/oanda.cpp"   // DB::HistoricalQuote::Oanda
#include "db/position/position.cpp"              // DB::Position
#include "db/price_action/price_action.cpp"      // DB::PriceAction
#include "db/quote/quote.cpp"                    // DB::Quote
#include "lib/formatted.cpp"                     // Formatted
#include "lib/performance/logger/logger.cpp"     // Performance::Logger
#include "lib/pg/pg.cpp"                         // Pg
#include "lib/utils/io.cpp"                      // ::utils::io
#include <iostream>                              // std::cout, std::endl
#include <list>                                  // std::list
#include <map>                                   // std::map
#include <sstream>                               // std::ostringstream
#include <stdexcept>                             // std::invalid_argument
#include <stdio.h>                               // printf
#include <string>                                // std::string, std::stoi

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"build_candles                          <SYMBOL> <OPTS>",
       "Build five minute candles for the given symbol"},
      {"import_historical_quotes               <SYMBOL> --api=<API_NAME> "
       "<OPTS>",
       "Import symbol's historical quotes"},
      {"log_snapshots                          --api=<API_NAME> <FLAGS>",
       "Print daily account performance for the given api key"},
      {"net_return                             <SYMBOL> <OPTS>",
       "Compute symbol's net return"},
      {"price_action                           <SYMBOL> <OPTS>",
       "Compute symbol's price action"},
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

// TODO: Re-factor into DB::Cli class
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

    std::map<std::string, std::string> default_flags = {
        {"end-at", ""},
        {"start-at", ""},
    };

    flags = ::utils::map::merge(default_flags, flags);

    Pg pg(flags);
    pg.connect();

    DB::Candle candle(pg, std::stoi(flags["duration-min"]),
                      upcased_args.front());

    candle.build({
        .debug = ::utils::io::flag_to_bool("debug", flags["debug"]),
        .end_at = flags["end-at"],
        .start_at = flags["start-at"],
    });

    pg.disconnect();

    exit(0);
  }

  if (command == "import_historical_quotes") {
    if (upcased_args.empty()) {
      std::string message =
          Formatted::error_message("Please provide at least one symbol.");

      throw std::invalid_argument(message);
    }

    std::map<std::string, std::string> default_flags = {
        {"batch", "10000"},
    };

    flags = ::utils::map::merge(default_flags, flags);

    const std::string api_name = flags["api"];

    if (api_name.empty()) {
      std::string message =
          Formatted::error_message("Please specify an api (--api=<API_NAME>).");

      throw std::invalid_argument(message);
    }

    Pg pg(flags);
    pg.connect();

    DB::HistoricalQuote::Base::init_args_t args = {
        .batch_size = flags["batch"],
        .conn = pg,
        .debug = ::utils::io::flag_to_bool("debug", flags["debug"]),
        .end_at = flags["end-at"],
        .start_at = flags["start-at"],
        .symbol = upcased_args.front(),
    };

    if (api_name == "alpaca") {
      DB::HistoricalQuote::Alpaca db_historical_quote(args);

      db_historical_quote.download();
    } else if (api_name == "oanda") {
      DB::HistoricalQuote::Oanda db_historical_quote(args);

      db_historical_quote.download();
    }

    pg.disconnect();

    exit(0);
  }

  if (command == "log_snapshots") {
    Pg pg(flags);
    pg.connect();

    Performance::Logger logger({
        .api_key = flags["api-key"],
        .api_name = flags["api"],
        .conn = pg,
        .debug = ::utils::io::flag_to_bool("debug", flags["debug"]),
        .end_at = flags["end-at"],
        .start_at = flags["start-at"],
    });

    logger.log_daily_snapshots();

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

  if (command == "price_action") {
    if (upcased_args.empty()) {
      std::string message =
          Formatted::error_message("Please provide at least one symbol.");

      throw std::invalid_argument(message);
    }

    std::map<std::string, std::string> default_flags = {
        {"end-at", ""},
        {"start-at", ""},
    };

    flags = ::utils::map::merge(default_flags, flags);

    Pg pg(flags);
    pg.connect();

    DB::PriceAction db_price_action({
        .conn = pg,
        .debug = ::utils::io::flag_to_bool("debug", flags["debug"]),
        .symbol = upcased_args.front(),
    });

    db_price_action.build({
        .end_at = flags["end-at"],
        .start_at = flags["start-at"],
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
