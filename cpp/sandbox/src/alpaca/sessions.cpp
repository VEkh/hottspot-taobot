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

    double current_balance;
    double min_balance;
    double original_balance;
    double overall_max_balance;
    double session_max_balance;
    long int min_balance_timestamp;
    long int overall_max_balance_timestamp;
    long int session_max_balance_timestamp;

    try {
      current_balance = session["current_balance"];
      min_balance = session["min_balance"];
      min_balance_timestamp = session["min_balance_timestamp"];
      original_balance = session["original_balance"];
      overall_max_balance = session["overall_max_balance"];
      overall_max_balance_timestamp = session["overall_max_balance_timestamp"];
      session_max_balance = session["max_balance"];
      session_max_balance_timestamp = session["max_balance_timestamp"];
    } catch (nlohmann::detail::type_error &) {
      std::cout << fmt.bold << fmt.red << std::endl;
      printf("😵 Corrupt value at: %s\n", it.key().c_str());
      std::cout << fmt.reset << std::endl;

      continue;
    }

    const double current_profit = current_balance - original_balance;
    const double current_profit_percent =
        100 * (current_balance - original_balance) / original_balance;
    const double session_max_profit = session_max_balance - original_balance;
    const double session_max_profit_percent =
        100 * (session_max_balance - original_balance) / original_balance;
    const double min_profit = min_balance - original_balance;
    const double min_profit_percent =
        100 * (min_balance - original_balance) / original_balance;
    const double overall_max_profit = overall_max_balance - original_balance;
    const double overall_max_profit_percent =
        100 * (overall_max_balance - original_balance) / original_balance;

    Formatted::Stream profit_color = current_profit >= 0 ? fmt.green : fmt.red;

    const int runtime = session["runtime"];

    const std::tm session_time =
        ::utils::time_::parse_timestamp(it.key(), "%Y-%m-%dT%H:%M");

    std::cout << fmt.bold << fmt.cyan << fmt.underline << std::endl;
    std::cout << std::put_time(&session_time, "%c");
    printf(" • Runtime: %s",
           ::utils::integer_::seconds_to_clock(runtime).c_str());
    std::cout << fmt.no_underline << profit_color << std::endl;
    printf("Current Balance:          $%'.2f (%+'.2f) (%+'.2f%%)\n",
           current_balance, current_profit, current_profit_percent);
    printf("Max Balance:              $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           session_max_balance, session_max_profit, session_max_profit_percent,
           ::utils::time_::date_string(session_max_balance_timestamp,
                                       "%H:%M %Z", "America/Chicago")
               .c_str());
    printf("Overall Max Balance:      $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           overall_max_balance, overall_max_profit, overall_max_profit_percent,
           ::utils::time_::date_string(overall_max_balance_timestamp,
                                       "%H:%M %Z", "America/Chicago")
               .c_str());
    printf("Min Balance:              $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           min_balance, min_profit, min_profit_percent,
           ::utils::time_::date_string(min_balance_timestamp, "%H:%M %Z",
                                       "America/Chicago")
               .c_str());
    printf("Original Balance:         $%'.2f\n", original_balance);

    if (session.contains("session_original_balance")) {
      const double session_original_balance =
          session["session_original_balance"];

      const double session_original_balance_profit =
          session_original_balance - original_balance;

      const double session_original_balance_profit_percent =
          (session_original_balance_profit / original_balance) * 100.0;

      printf("Session Original Balance: $%'.2f (%+'.2f) (%+'.2f%%)\n",
             session_original_balance, session_original_balance_profit,
             session_original_balance_profit_percent);
    }
  }

  std::cout << fmt.reset << fmt.cyan;
}
} // namespace Sessions
} // namespace Alpaca

#endif
