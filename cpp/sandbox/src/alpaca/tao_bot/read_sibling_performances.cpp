#ifndef ALPACA__TAO_BOT_read_sibling_performances
#define ALPACA__TAO_BOT_read_sibling_performances

#include "deps.cpp"                     // json, nlohmann
#include "lib/formatted.cpp"            // Formatted
#include "lib/utils/io.cpp"             // ::utils::io
#include "read_sibling_performance.cpp" // read_sibling_performance
#include "tao_bot.h"                    // Alpaca::TaoBot, fmt
#include <dirent.h> // DIR, closedir, dirent, opendir, readdir
#include <fstream>  // std::ifstream
#include <iostream> // std::cout, std::endl
#include <list>     // std::list
#include <string>   // std::string

/*
 * std::cmatch
 * std::regex
 * std::regex_constants
 * std::regex_search
 */
#include <regex>

std::list<Alpaca::TaoBot::performance_t>
Alpaca::TaoBot::read_sibling_performances() {
  std::string performance_directory =
      std::string(APP_DIR) + "/data/alpaca/performance/";

  std::list<performance_t> out;

  DIR *dir = opendir(performance_directory.c_str());
  dirent *entity;

  if (dir == nullptr) {
    std::cout << fmt.bold << fmt.red;
    puts("❗ There is no performance directory from which to detect a loss "
         "leader.");
    std::cout << fmt.reset;

    return out;
  }

  while ((entity = readdir(dir)) != nullptr) {
    if (!std::regex_search(entity->d_name, std::regex("\\.json$"))) {
      continue;
    }

    std::cmatch match;
    std::regex_search(entity->d_name, match, std::regex("(\\w+).json$"));

    const std::string file_symbol = std::string(match[1]);

    if (std::regex_search(
            file_symbol,
            std::regex(this->symbol, std::regex_constants::icase))) {
      continue;
    }

    json performance_json = read_sibling_performance(file_symbol);
    performance_t sibling_performance;

    if (!performance_json.contains("are_funds_sufficient")) {
      continue;
    }

    if (!performance_json.contains("current_balance")) {
      continue;
    }

    if (!performance_json.contains("current_loss_streak_balance")) {
      continue;
    }

    if (!performance_json.contains("is_position_open")) {
      continue;
    }

    if (!performance_json.contains("max_balance")) {
      continue;
    }

    sibling_performance.are_funds_sufficient =
        performance_json["are_funds_sufficient"];
    sibling_performance.current_balance = performance_json["current_balance"];
    sibling_performance.current_loss_streak_balance =
        performance_json["current_loss_streak_balance"];
    sibling_performance.is_position_open = performance_json["is_position_open"];
    sibling_performance.max_balance = performance_json["max_balance"];
    sibling_performance.symbol = file_symbol;

    out.push_back(sibling_performance);
  }

  closedir(dir);

  return out;
}

#endif
