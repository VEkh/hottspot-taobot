#ifndef ALPACA__CLI_H
#define ALPACA__CLI_H

#include "lib/cli/cli.cpp" // ::Cli
#include <map>             // std::map
#include <string>          // std::string

namespace Alpaca {
using BaseCli = ::Cli;

class Cli : public BaseCli {
public:
  Cli(int, char **);

private:
  void cancel_orders();
  void fetch_asset();
  void fetch_quote();
  void log_benchmark();
  void quotes_stream();
  void quotes_watch();
  void stream_account();
  void tao_bot();

  void execute() override;
};
}; // namespace Alpaca

#endif
