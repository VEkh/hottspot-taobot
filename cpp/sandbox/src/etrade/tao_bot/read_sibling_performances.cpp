#ifndef ETRADE__TAO_BOT_read_sibling_performances
#define ETRADE__TAO_BOT_read_sibling_performances

#include "deps.cpp"         // json
#include "lib/utils/io.cpp" // ::utils::io
#include "tao_bot.h"        // ETrade::TaoBot, fmt
#include <dirent.h>         // DIR, closedir, dirent, opendir, readdir
#include <fstream>          // std::ifstream
#include <iostream>         // std::cout
#include <list>             // std::list
#include <string>           // std::string

/*
 * std::cmatch
 * std::regex
 * std::regex_constants
 * std::regex_search
 */
#include <regex>

std::list<ETrade::TaoBot::performance_t>
ETrade::TaoBot::read_sibling_performances() {
  std::string performance_directory =
      std::string(DATA_DIR) + "/etrade/performance/";

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

    const std::string performance_filepath =
        performance_directory + entity->d_name;

    std::ifstream file;

    try {
      file = ::utils::io::read_file(performance_filepath.c_str());
    } catch (std::invalid_argument &) {
      return read_sibling_performances();
    }

    json performance_json;
    file >> performance_json;
    file.close();

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
