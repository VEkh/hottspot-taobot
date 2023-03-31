#ifndef OANDA_SESSIONS
#define OANDA_SESSIONS

#include "deps.cpp"              // json
#include "lib/formatted.cpp"     // ::utils::io
#include "lib/utils/integer.cpp" // ::utils::integer_
#include "lib/utils/io.cpp"      // Formatted
#include "lib/utils/time.cpp"    // ::utils::time_
#include <ctime>                 // std::tm
#include <fstream>               // std::ifstream
#include <iomanip>               // std:put_time
#include <iostream>              // std::cout, std::endl
#include <locale.h>              // setlocale
#include <stdio.h>               // printf
#include <string>                // std::string

namespace Oanda {
namespace Sessions {
void log() {
  setlocale(LC_NUMERIC, "");
  Formatted::fmt_stream_t fmt = Formatted::stream();

  const std::string filepath =
      std::string(DATA_DIR) + "/oanda/performance/account.json";

  std::ifstream file;
  json sessions;

  try {
    file = ::utils::io::read_file(filepath.c_str());
    file >> sessions;
    file.close();
  } catch (...) {
    std::cout << fmt.bold << fmt.red;
    puts("❌ Failed to read sessions.");
    std::cout << fmt.reset << std::endl;
    return;
  }

  for (json::iterator it = sessions.begin(); it != sessions.end(); it++) {
    json session = it.value();

    const double current_equity = session["current_balance"];
    const double max_equity = session["overall_max_balance"];
    const double min_equity = session["min_balance"];
    const double original_equity = session["original_balance"];
    const double session_max_equity = session["max_balance"];
    const double max_equity_timestamp =
        session["overall_max_balance_timestamp"];
    const double min_equity_timestamp = session["min_balance_timestamp"];
    const double session_max_equity_timestamp =
        session["max_balance_timestamp"];

    const double current_profit = current_equity - original_equity;
    const double current_profit_percent =
        100 * (current_equity - original_equity) / original_equity;
    const double max_profit = max_equity - original_equity;
    const double max_profit_percent =
        100 * (max_equity - original_equity) / original_equity;
    const double min_profit = min_equity - original_equity;
    const double min_profit_percent =
        100 * (min_equity - original_equity) / original_equity;
    const double overall_max_profit = max_equity - original_equity;
    const double overall_max_profit_percent =
        100 * (max_equity - original_equity) / original_equity;

    Formatted::Stream profit_color = current_profit >= 0 ? fmt.green : fmt.red;

    const int runtime = session["runtime"];

    const std::tm session_time =
        ::utils::time_::parse_timestamp(it.key(), "%Y-%m-%dT%H:%M");

    std::cout << fmt.bold << fmt.cyan << fmt.underline << std::endl;
    std::cout << std::put_time(&session_time, "%c");
    printf(" • Runtime: %s",
           ::utils::integer_::seconds_to_clock(runtime).c_str());
    std::cout << fmt.no_underline << profit_color << std::endl;
    printf("Current Equity:          $%'.2f (%+'.2f) (%+'.2f%%)\n",
           current_equity, current_profit, current_profit_percent);
    printf("Max Equity:              $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           max_equity, max_profit, max_profit_percent,
           ::utils::time_::date_string(max_equity_timestamp, "%H:%M %Z",
                                       "America/Chicago")
               .c_str());
    printf("Overall Max Equity:      $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           max_equity, overall_max_profit, overall_max_profit_percent,
           ::utils::time_::date_string(max_equity_timestamp, "%H:%M %Z",
                                       "America/Chicago")
               .c_str());
    printf("Min Equity:              $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           min_equity, min_profit, min_profit_percent,
           ::utils::time_::date_string(min_equity_timestamp, "%H:%M %Z",
                                       "America/Chicago")
               .c_str());
    printf("Original Equity:         $%'.2f\n", original_equity);

    if (session.contains("session_original_balance")) {
      const double session_original_equity =
          session["session_original_balance"];

      const double session_original_equity_profit =
          session_original_equity - original_equity;

      const double session_original_equity_profit_percent =
          (session_original_equity_profit / original_equity) * 100.0;

      printf("Session Original Equity: $%'.2f (%+'.2f) (%+'.2f%%)\n",
             session_original_equity, session_original_equity_profit,
             session_original_equity_profit_percent);
    }
  }

  std::cout << fmt.reset << fmt.cyan;
}
} // namespace Sessions
} // namespace Oanda

#endif
