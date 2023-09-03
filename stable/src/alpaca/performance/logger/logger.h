#ifndef ALPACA__PERFORMANCE__LOGGER_H
#define ALPACA__PERFORMANCE__LOGGER_H

#include <string> // std::string

namespace Alpaca {
namespace Performance {
class Logger {
public:
  Logger(){};

  void log_benchmark();

private:
  json read_json_file(const std::string);
};
} // namespace Performance
} // namespace Alpaca

#endif
