#ifndef ETRADE__TAO_BOT_get_loss_leader
#define ETRADE__TAO_BOT_get_loss_leader

#include "deps.cpp"         // json
#include "lib/utils/io.cpp" // ::utils::io
#include "tao_bot.h"        // ETrade::TaoBot, fmt
#include <algorithm>        // std::min
#include <dirent.h>         // DIR, closedir, dirent, opendir, readdir
#include <fstream>          // std::ifstream
#include <iostream>         // std::cout
#include <string>           // std::string

/*
 * std::cmatch
 * std::regex
 * std::regex_constants
 * std::regex_search
 */
#include <regex>

std::string ETrade::TaoBot::get_loss_leader() {
  std::string performance_directory =
      std::string(APP_DIR) + "/data/etrade/performance/";

  DIR *dir = opendir(performance_directory.c_str());
  dirent *entity;

  if (dir == nullptr) {
    std::cout << fmt.bold << fmt.red;
    puts("❗ There is no performance directory from which to detect a loss "
         "leader.");
    std::cout << fmt.reset;

    return "";
  }

  std::string loss_leader;
  double min_deficit = 0.00;

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
      return get_loss_leader();
    }

    json performance_json;
    file >> performance_json;
    file.close();

    if (!performance_json.contains("current_balance")) {
      continue;
    }

    if (!performance_json.contains("max_balance")) {
      continue;
    }

    const double current_balance = performance_json["current_balance"];
    const double max_balance = performance_json["max_balance"];
    const double deficit = current_balance - max_balance;

    if (deficit <= -0.005 * this->account_balance.balance &&
        deficit < min_deficit) {
      min_deficit = deficit;
      loss_leader = file_symbol;
    }
  }

  closedir(dir);

  return loss_leader;
}

#endif
