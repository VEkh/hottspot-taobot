#ifndef DB__CLI_net_return
#define DB__CLI_net_return

#include "cli.h"                    // DB::Cli
#include "db/position/position.cpp" // DB::Position
#include "lib/formatted.cpp"        // Formatted
#include "lib/utils/io.cpp"         // ::utils::io
#include <map>                      // std::map
#include <string>                   // std::string, std::stoi

void DB::Cli::net_return() {
  if (this->upcased_args.empty()) {
    const std::string message =
        Formatted::error_message("Please provide at least one symbol.");

    throw std::invalid_argument(message);
  }

  std::map<std::string, std::string> default_flags = {
      {"end-at", ""},
      {"limit", "0"},
      {"project", "alpaca"},
      {"start-at", ""},
  };

  this->flags = ::utils::map::merge(default_flags, this->flags);

  Pg pg(this->flags);
  pg.connect();

  DB::Position db_position(pg);

  db_position.net_return({
      .api_key = this->flags["api-key"],
      .debug = ::utils::io::flag_to_bool("debug", this->flags["debug"]),
      .end_at = this->flags["end-at"],
      .limit = std::stoi(this->flags["limit"]),
      .log_positions = ::utils::io::flag_to_bool("log-positions",
                                                 this->flags["log-positions"]),
      .project = this->flags["project"],
      .start_at = this->flags["start-at"],
      .symbol = this->upcased_args.front(),
  });

  pg.disconnect();
}

#endif
