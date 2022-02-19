#include "deps.cpp"          // json
#include "lib/formatted.cpp" // Formatted
#include <algorithm>         // std::max
#include <ctime>             // std::mktime, std::tm
#include <fstream>           // std::ifstream, std::ios
#include <iomanip>           // std::get_time
#include <iostream>          // std::cout, std::endl
#include <locale.h>          // setlocale
#include <math.h>            // abs
#include <sstream>           // std::istringstream
#include <stdexcept>         // std::invalid_argument
#include <stdio.h>           // printf
#include <string>            // std::string

namespace Alpaca {
namespace Returns {
char sign(double n) { return n >= 0 ? '+' : '-'; };

json load() {
  std::string path = std::string(APP_DIR) + "/data/alpaca/returns.json";
  std::ifstream file(path.c_str(), std::ios::in);

  if (!file.good()) {
    std::string error_message = Formatted::error_message(
        "Returns data missing at " + std::string(path));

    throw std::invalid_argument(error_message);
  }

  json returns_json;
  file >> returns_json;
  file.close();

  return returns_json;
}

std::tm parse_date(std::string in) {
  std::tm datetime = {};
  std::istringstream date_string(in);

  date_string >> std::get_time(&datetime, "%Y-%m-%d");

  std::mktime(&datetime);

  return datetime;
}

void log() {
  setlocale(LC_NUMERIC, "");
  Formatted::fmt_stream_t fmt = Formatted::stream();

  json returns = load();
  json all_returns = returns["all"];
  json qqq_returns = returns["qqq"];

  bool is_loss_streak_broken = false;
  bool is_week_total_complete = false;
  bool is_win_streak_broken = false;
  double grand_total = 0.00;
  double avg_profit_ratio = 0.00;
  double avg_qqq_profit_ratio = 0.00;
  double week_total = 0.00;
  int all_returns_length = all_returns.size();
  int consecutive_losses = 0;
  int consecutive_wins = 0;
  int qqq_returns_length = qqq_returns.size();
  int start_weekday = 0;
  int total_losses = 0;
  int total_wins = 0;

  json::reverse_iterator it = all_returns.rbegin();
  json todays_return_json = it.value();
  json::reverse_iterator qit = qqq_returns.rbegin();
  json todays_qqq_return_json = qit.value();

  const double DAILY_SALARY = 506.71;
  const double todays_close = todays_return_json["close"];
  const double todays_open = todays_return_json["open"];
  const double todays_profit_dollars = todays_close - todays_open;
  const double todays_profit_ratio = todays_profit_dollars / todays_open;
  const double todays_profit_salary_ratio =
      todays_profit_dollars / DAILY_SALARY;

  const double todays_qqq_close = todays_qqq_return_json["close"];
  const double todays_qqq_open = todays_qqq_return_json["open"];
  const double todays_qqq_profit_ratio =
      (todays_qqq_close - todays_qqq_open) / todays_qqq_open;

  for (; it != all_returns.rend(); it++) {
    const std::tm parsed_date = parse_date(it.key());
    json return_json = it.value();

    const double close = return_json["close"];
    const double open = return_json["open"];
    const double profit_dollars = close - open;
    const double profit_ratio = profit_dollars / open;

    start_weekday = std::max(start_weekday, parsed_date.tm_wday);

    is_week_total_complete = (bool)(is_week_total_complete ||
                                    (it != all_returns.rbegin() &&
                                     parsed_date.tm_wday >= start_weekday));

    avg_profit_ratio += profit_ratio / all_returns_length;
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

  for (; qit != qqq_returns.rend(); qit++) {
    json return_json = qit.value();

    const double close = return_json["close"];
    const double open = return_json["open"];
    const double profit_dollars = close - open;
    const double profit_ratio = profit_dollars / open;

    avg_qqq_profit_ratio += profit_ratio / qqq_returns_length;
  }

  std::cout << fmt.bold << fmt.yellow << std::endl;
  printf("* Wins / Losses: %iW (Consecutive: %i) %iL (Consecutive: %i)\n",
         total_wins, consecutive_wins, total_losses, consecutive_losses);

  std::cout << fmt.cyan;
  printf("* Latest Return: %c$%'.2f (%+.2f%%) (%+.2f%% Daily Salary) (vs. "
         "QQQ: %+.2f%%)\n",
         sign(todays_profit_dollars), abs(todays_profit_dollars),
         todays_profit_ratio * 100, todays_profit_salary_ratio * 100,
         todays_qqq_profit_ratio * 100);

  printf("* Week's Return: %c$%'.2f \n", sign(week_total), abs(week_total));
  printf("* Total Return: %c$%'.2f\n", sign(grand_total), abs(grand_total));

  std::cout << fmt.yellow;
  printf("* Average Return: %+.2f%% • Average QQQ Return: %+.2f%%\n",
         avg_profit_ratio * 100, avg_qqq_profit_ratio * 100);
  std::cout << fmt.reset << std::endl;
}
} // namespace Returns
} // namespace Alpaca
