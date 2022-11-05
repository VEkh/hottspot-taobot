#ifndef ALPACA_SESSIONS
#define ALPACA_SESSIONS

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

namespace Alpaca {
namespace Sessions {
void log() {
  setlocale(LC_NUMERIC, "");
  Formatted::fmt_stream_t fmt = Formatted::stream();

  const std::string filepath =
      std::string(APP_DIR) + "/data/alpaca/performance/account.json";

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

    const double current_balance = session["current_balance"];
    const double max_balance = session["max_balance"];
    const double min_balance = session["min_balance"];
    const double original_balance = session["original_balance"];
    const int max_balance_timestamp = session["max_balance_timestamp"];
    const int min_balance_timestamp = session["min_balance_timestamp"];

    const double current_profit = current_balance - original_balance;
    const double current_profit_percent =
        100 * (current_balance - original_balance) / original_balance;
    const double max_profit = max_balance - original_balance;
    const double max_profit_percent =
        100 * (max_balance - original_balance) / original_balance;
    const double min_profit = min_balance - original_balance;
    const double min_profit_percent =
        100 * (min_balance - original_balance) / original_balance;

    Formatted::Stream profit_color = current_profit >= 0 ? fmt.green : fmt.red;

    const int runtime = session["runtime"];

    const std::tm session_time =
        ::utils::time_::parse_timestamp(it.key(), "%Y-%m-%dT%H:%M");

    std::cout << fmt.bold << fmt.cyan << fmt.underline << std::endl;
    std::cout << std::put_time(&session_time, "%c");
    printf(" • Runtime: %s",
           ::utils::integer_::seconds_to_clock(runtime).c_str());
    std::cout << fmt.no_underline << profit_color << std::endl;
    printf("Current Balance:        $%'.2f (%+'.2f) (%+'.2f%%)\n",
           current_balance, current_profit, current_profit_percent);
    printf("Max Balance:            $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           max_balance, max_profit, max_profit_percent,
           ::utils::time_::date_string(max_balance_timestamp, "%H:%M %Z",
                                       "America/Chicago")
               .c_str());
    printf("Overall Max Balance:    $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           overall_max_balance, overall_max_profit, overall_max_profit_percent,
           ::utils::time_::date_string(overall_max_balance_timestamp,
                                       "%H:%M %Z", "America/Chicago")
               .c_str());
    printf("Min Balance:            $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           min_balance, min_profit, min_profit_percent,
           ::utils::time_::date_string(min_balance_timestamp, "%H:%M %Z",
                                       "America/Chicago")
               .c_str());
    printf("Original Balance:       $%'.2f\n", original_balance);
  }

  std::cout << fmt.reset << fmt.cyan;
}
} // namespace Sessions
} // namespace Alpaca

#endif
