#ifndef ALPACA__PERFORMANCE__LOGGER_log_benchmark
#define ALPACA__PERFORMANCE__LOGGER_log_benchmark

#include "deps.cpp"            // json
#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/float.cpp" // ::utils::float_
#include "lib/utils/time.cpp"  // ::utils::time_
#include "logger.h"            // Alpaca::Performance::Logger
#include "read_json_file.cpp"  // read_json_file
#include <algorithm>           // std::max
#include <iostream>            // std::cout, std::endl
#include <locale.h>            // setlocale
#include <math.h>              // abs
#include <stdio.h>             // printf
#include <time.h>              // tm

void Alpaca::Performance::Logger::log_benchmark() {
  setlocale(LC_NUMERIC, "");
  Formatted::fmt_stream_t fmt = Formatted::stream();

  json returns = read_json_file("benchmark.json");
  json hottspot_returns = returns["HOTT"];
  json nasdaq_returns = returns["NDX"];
  json sp500_returns = returns["SPX"];

  bool is_loss_streak_broken = false;
  bool is_week_total_complete = false;
  bool is_win_streak_broken = false;
  double grand_total = 0.00;
  double avg_profit_ratio = 0.00;
  double avg_nasdaq_profit_ratio = 0.00;
  double avg_sp500_profit_ratio = 0.00;
  double week_total = 0.00;
  int hottspot_returns_length = hottspot_returns.size();
  int consecutive_losses = 0;
  int consecutive_wins = 0;
  int nasdaq_returns_length = nasdaq_returns.size();
  int sp500_returns_length = sp500_returns.size();
  int max_week_of_year = 0;
  int total_losses = 0;
  int total_wins = 0;

  json::reverse_iterator it = hottspot_returns.rbegin();
  json todays_return_json = it.value();
  json::reverse_iterator nasdaq_it = nasdaq_returns.rbegin();
  json::reverse_iterator sp500_it = sp500_returns.rbegin();
  json todays_nasdaq_return_json = nasdaq_it.value();
  json todays_sp500_return_json = sp500_it.value();

  const double NINE_TO_FIVE_SALARY = 576.92;
  const double todays_close = todays_return_json["close"];
  const double todays_open = todays_return_json["open"];
  const double todays_profit_dollars = todays_close - todays_open;
  const double todays_profit_ratio = todays_profit_dollars / todays_open;
  const double todays_profit_salary_ratio =
      todays_profit_dollars / NINE_TO_FIVE_SALARY;

  const double todays_nasdaq_close = todays_nasdaq_return_json["close"];
  const double todays_nasdaq_open = todays_nasdaq_return_json["open"];
  const double todays_nasdaq_profit_ratio =
      (todays_nasdaq_close - todays_nasdaq_open) / todays_nasdaq_open;

  const double todays_sp500_close = todays_sp500_return_json["close"];
  const double todays_sp500_open = todays_sp500_return_json["open"];
  const double todays_sp500_profit_ratio =
      (todays_sp500_close - todays_sp500_open) / todays_sp500_open;

  for (; it != hottspot_returns.rend(); it++) {
    const std::tm parsed_date =
        ::utils::time_::parse_timestamp(it.key(), "%Y-%m-%d");
    json return_json = it.value();

    const double close = return_json["close"];
    const double open = return_json["open"];
    const double profit_dollars = close - open;
    const double profit_ratio = profit_dollars / open;
    const int week_of_year =
        (parsed_date.tm_yday - parsed_date.tm_wday + 7) / 7;

    max_week_of_year = std::max(max_week_of_year, week_of_year);

    is_week_total_complete =
        (bool)(is_week_total_complete || week_of_year < max_week_of_year);

    avg_profit_ratio += profit_ratio / hottspot_returns_length;
    grand_total += profit_dollars;

    if (!is_week_total_complete) {
      week_total += profit_dollars;
    }

    if (profit_dollars >= 0) {
      is_loss_streak_broken = true;
      total_wins++;

      if (!is_win_streak_broken) {
        consecutive_wins++;
      }
    }

    if (profit_dollars < 0) {
      is_win_streak_broken = true;
      total_losses++;

      if (!is_loss_streak_broken) {
        consecutive_losses++;
      }
    }
  }

  const double win_percentage =
      ((double)total_wins / (total_wins + total_losses)) * 100.0;

  for (; nasdaq_it != nasdaq_returns.rend(); nasdaq_it++) {
    json return_json = nasdaq_it.value();

    const double close = return_json["close"];
    const double open = return_json["open"];
    const double profit_dollars = close - open;
    const double profit_ratio = profit_dollars / open;

    avg_nasdaq_profit_ratio += profit_ratio / nasdaq_returns_length;
  }

  for (; sp500_it != sp500_returns.rend(); sp500_it++) {
    json return_json = sp500_it.value();

    const double close = return_json["close"];
    const double open = return_json["open"];
    const double profit_dollars = close - open;
    const double profit_ratio = profit_dollars / open;

    avg_sp500_profit_ratio += profit_ratio / sp500_returns_length;
  }

  std::cout << fmt.bold << fmt.yellow << std::endl;
  printf(
      "* Wins / Losses: %iW (%.2f%%) (Consecutive: %i) %iL (Consecutive: %i)\n",
      total_wins, win_percentage, consecutive_wins, total_losses,
      consecutive_losses);

  std::cout << fmt.cyan;
  printf("* Latest Return: %c$%'.2f (%+.2f%%) (%+.2f%% 9-5 Salary)"
         " (vs. NASDAQ: %+.2f%%) (vs. S&P 500: %+.2f%%)\n",
         ::utils::float_::sign_char(todays_profit_dollars),
         abs(todays_profit_dollars), todays_profit_ratio * 100,
         todays_profit_salary_ratio * 100, todays_nasdaq_profit_ratio * 100,
         todays_sp500_profit_ratio * 100);

  printf("* Week's Return: %c$%'.2f • Total Return: %c$%'.2f\n",
         ::utils::float_::sign_char(week_total), abs(week_total),
         ::utils::float_::sign_char(grand_total), abs(grand_total));

  std::cout << fmt.yellow;
  printf("* Average Return: %+.2f%% • Average NASDAQ Return: %+.2f%% • Average "
         "S&P 500 Return: %+.2f%%\n",
         avg_profit_ratio * 100, avg_nasdaq_profit_ratio * 100,
         avg_sp500_profit_ratio * 100);
  std::cout << fmt.reset << std::endl;
}

#endif
