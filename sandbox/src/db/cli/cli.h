#ifndef DB__CLI_H
#define DB__CLI_H

#include "lib/cli/cli.cpp" // ::Cli
#include <map>             // std::map
#include <string>          // std::string

namespace DB {
using BaseCli = ::Cli;

class Cli : public BaseCli {
public:
  Cli(int, char **);

private:
  void build_candles();
  void import_historical_quotes();
  void log_snapshots();
  void net_return();

  void execute() override;
};
} // namespace DB

#endif
