#ifndef ALPACA__TAO_BOT_read_sibling_performance
#define ALPACA__TAO_BOT_read_sibling_performance

/*
 * Alpaca::TaoBot
 * order_t
 * position_t
 */
#include "tao_bot.h"

#include "deps.cpp"         // json, nlohmann
#include "lib/utils/io.cpp" // ::utils::io
#include <fstream>          // std::ifstream
#include <stdexcept>        // std::invalid_argument
#include <string>           // std::string

json Alpaca::TaoBot::read_sibling_performance(std::string sibling_symbol) {
  const std::string filepath = std::string(APP_DIR) +
                               "/data/alpaca/performance/" + sibling_symbol +
                               ".json";

  json performance_json;
  std::ifstream file;

  try {
    file = ::utils::io::read_file(filepath.c_str());
    file >> performance_json;
    file.close();
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message = Formatted::error_message(
        std::string(
            "ALPACA__TAO_BOT_read_sibling_performance: JSON parse error for ") +
        sibling_symbol);

    std::cout << error_message << fmt.reset << std::endl;

    return read_sibling_performance(symbol);
  } catch (std::invalid_argument &) {
    std::string error_message = Formatted::error_message(
        std::string(
            "ALPACA__TAO_BOT_read_sibling_performance: Invalid argument for ") +
        sibling_symbol);

    std::cout << error_message << fmt.reset << std::endl;

    return performance_json;
  }

  return performance_json;
}

#endif
