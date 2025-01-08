#ifndef DB__CLI_import_historical_quotes
#define DB__CLI_import_historical_quotes

#include "cli.h"                                 // DB::Cli
#include "db/historical_quote/alpaca/alpaca.cpp" // DB::HistoricalQuote::Alpaca
#include "db/historical_quote/base/base.cpp"     // DB::HistoricalQuote::Base
#include "db/historical_quote/oanda/oanda.cpp"   // DB::HistoricalQuote::Oanda
#include "lib/formatted.cpp"                     // Formatted
#include "lib/pg/pg.cpp"                         // Pg
#include "lib/utils/io.cpp"                      // ::utils::io
#include "lib/utils/map.cpp"                     // ::utils::map
#include <map>                                   // std::map
#include <stdexcept>                             // std::invalid_argument
#include <string>                                // std::string

void DB::Cli::import_historical_quotes() {
  if (this->upcased_args.empty()) {
    const std::string message =
        Formatted::error_message("Please provide at least one symbol.");

    throw std::invalid_argument(message);
  }

  std::map<std::string, std::string> default_flags = {
      {"batch", "10000"},
  };

  this->flags = ::utils::map::merge(default_flags, this->flags);

  const std::string api_name = this->flags["api"];

  if (api_name.empty()) {
    const std::string message =
        Formatted::error_message("Please specify an api (--api=<API_NAME>).");

    throw std::invalid_argument(message);
  }

  Pg pg(this->flags);
  pg.connect();

  DB::HistoricalQuote::Base::init_args_t init_args = {
      .batch_size = this->flags["batch"],
      .conn = pg,
      .debug = ::utils::io::flag_to_bool("debug", this->flags["debug"]),
      .end_at = this->flags["end-at"],
      .start_at = this->flags["start-at"],
      .symbol = this->upcased_args.front(),
  };

  if (api_name == "alpaca") {
    DB::HistoricalQuote::Alpaca db_historical_quote(init_args);

    db_historical_quote.download();
  } else if (api_name == "oanda") {
    DB::HistoricalQuote::Oanda db_historical_quote(init_args);

    db_historical_quote.download();
  }

  pg.disconnect();
}

#endif
