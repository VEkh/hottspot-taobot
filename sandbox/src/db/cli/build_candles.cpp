#ifndef DB__CLI_build_candles
#define DB__CLI_build_candles

#include "cli.h"                // DB::Cli
#include "db/candle/candle.cpp" // DB::Candle
#include "lib/formatted.cpp"    // Formatted
#include "lib/pg/pg.cpp"        // Pg
#include "lib/utils/io.cpp"     // ::utils::io
#include "lib/utils/map.cpp"    // ::utils::map
#include <stdexcept>            // std::invalid_argument
#include <string>               // std::string, std::stoi

void DB::Cli::build_candles() {
  if (this->upcased_args.empty()) {
    const std::string message =
        Formatted::error_message("Please provide at least one symbol.");

    throw std::invalid_argument(message);
  }

  if (this->flags["duration-min"].empty()) {
    const std::string message = Formatted::error_message(
        "Please provide duration minutes with the --duration-min flag.");

    throw std::invalid_argument(message);
  }

  std::map<std::string, std::string> default_flags = {
      {"end-at", ""},
      {"start-at", ""},
  };

  this->flags = ::utils::map::merge(default_flags, this->flags);

  Pg pg(this->flags);
  pg.connect();

  DB::Candle candle(pg, std::stoi(this->flags["duration-min"]),
                    this->upcased_args.front());

  candle.build({
      .debug = ::utils::io::flag_to_bool("debug", this->flags["debug"]),
      .end_at = this->flags["end-at"],
      .start_at = this->flags["start-at"],
  });

  pg.disconnect();
}

#endif
