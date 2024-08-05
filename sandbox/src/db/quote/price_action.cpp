#ifndef DB__QUOTE_price_action
#define DB__QUOTE_price_action

#include "get_last.cpp"                                // get_last
#include "lib/nyse_availability/nyse_availability.cpp" // NyseAvailability
#include "lib/utils/integer.cpp"                       // ::utils::integer_
#include "lib/utils/time.cpp"                          // ::utils::time_
#include "quote.h"   // DB::Quote, candle_t, fmt, price_action_args_t, quote_t
#include <algorithm> // std::max, std::min
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf
#include <string>    // std::stod, std::string
#include <time.h>    // time

double DB::Quote::price_action(const price_action_args_t args) {
  const double process_timer_start = time(nullptr);

  const std::string symbol = args.symbol;

  std::cout << fmt.bold << fmt.underline << std::endl;
  std::cout << fmt.cyan << symbol;

  std::cout << fmt.bold << fmt.yellow;
  printf("'s Price Action\n");
  std::cout << std::endl << fmt.reset;

  double end_at = time(nullptr);
  double start_at = 0.0;

  if (!args.end_at.empty()) {
    end_at = this->db_utils.timestamp_to_epoch(args.end_at, "UTC");
  }

  if (!args.start_at.empty()) {
    start_at = this->db_utils.timestamp_to_epoch(args.start_at, "UTC");
  }

  this->db_utils.set_param({"statement_timeout", "600000"});

  NyseAvailability market_availability(this->conn);

  std::cout << fmt.bold << fmt.yellow;
  printf("💿 Reading Quotes...\n");
  std::cout << std::endl << fmt.reset;

  const std::list<quote_t> quotes = get_last({
      .debug = args.debug,
      .end_at = end_at,
      .sort_direction = args.sort_direction,
      .start_at = start_at,
      .symbol = symbol,
  });

  const double quotes_get_seconds = time(nullptr) - process_timer_start;

  std::cout << fmt.bold << fmt.cyan;
  printf("%'d", (int)quotes.size());

  std::cout << fmt.yellow;
  printf(" %s quotes loaded in %s\n", symbol.c_str(),
         ::utils::integer_::seconds_to_clock(quotes_get_seconds).c_str());
  std::cout << std::endl << fmt.reset;

  double price_action_sum = 0.0;
  int days_n = 0;

  double avg_price_action = 0.0;

  candle_t day_candle;

  for (const quote_t quote : quotes) {
    if (!market_availability.is_market_open(quote.timestamp)) {
      continue;
    }

    if (day_candle.closed_at && quote.timestamp > day_candle.closed_at) {
      const double day_price_action =
          100.0 * day_candle.range() / day_candle.open;

      days_n++;
      price_action_sum += day_price_action;

      avg_price_action = days_n ? price_action_sum / days_n : 0.0;

      std::cout << fmt.bold << fmt.magenta;
      printf("%s %s Candle\n",
             ::utils::time_::date_string(day_candle.opened_at, "%F",
                                         "America/Chicago")
                 .c_str(),
             symbol.c_str());
      std::cout << fmt.reset;

      std::cout << fmt.bold << fmt.cyan;
      printf("--------------------------------------\n");
      printf("Open:  %.2f • Opened At: %s\n", day_candle.open,
             ::utils::time_::date_string(day_candle.opened_at, "%R CT",
                                         "America/Chicago")
                 .c_str());

      printf("Close: %.2f • Closed At: %s\n", day_candle.close,
             ::utils::time_::date_string(day_candle.closed_at, "%R CT",
                                         "America/Chicago")
                 .c_str());

      printf("High:  %.2f • High At: %s\n", day_candle.high,
             ::utils::time_::date_string(day_candle.high_at, "%R CT",
                                         "America/Chicago")
                 .c_str());

      printf("Low:   %.2f • Low At: %s\n", day_candle.low,
             ::utils::time_::date_string(day_candle.low_at, "%R CT",
                                         "America/Chicago")
                 .c_str());
      printf("--------------------------------------\n");

      std::cout << fmt.bold << fmt.green;
      printf("💸 Price Action: %.2f%%\n", day_price_action);
      std::cout << std::endl << fmt.reset;

      std::cout << fmt.bold << fmt.yellow;
      printf("📅 Days Processed:     %i\n", days_n);

      printf("🤑 Avg Price Action:   ");
      std::cout << fmt.green;
      printf("%.2f%%\n", avg_price_action);

      const int process_duration = time(nullptr) - process_timer_start;
      std::cout << fmt.bold << fmt.yellow;
      printf("⌚ Time Running:       %s\n",
             ::utils::integer_::seconds_to_clock(process_duration).c_str());

      std::cout << std::endl << fmt.reset;

      day_candle = candle_t();

      if (!market_availability.is_market_open(quote.timestamp)) {
        continue;
      }
    }

    if (!day_candle.opened_at) {
      day_candle.closed_at =
          market_availability.market_close_epoch(quote.timestamp);

      day_candle.opened_at =
          market_availability.market_open_epoch(quote.timestamp);
    }

    const double mid = quote.mid();

    day_candle.close = mid;

    day_candle.open = day_candle.open ? day_candle.open : mid;

    day_candle.high = std::max(day_candle.high, mid);
    day_candle.low = std::min(day_candle.low, mid);

    if (day_candle.high == mid) {
      day_candle.high_at = quote.timestamp;
    }

    if (day_candle.low == mid) {
      day_candle.low_at = quote.timestamp;
    }
  }

  const int process_duration = time(nullptr) - process_timer_start;

  std::cout << fmt.bold << fmt.cyan;
  printf("🎉 Completed in %s\n",
         ::utils::integer_::seconds_to_clock(process_duration).c_str());
  std::cout << std::endl << fmt.reset;

  return avg_price_action;
}

#endif
