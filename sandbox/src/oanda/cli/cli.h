#ifndef OANDA__CLI_H
#define OANDA__CLI_H

#include "lib/cli/cli.cpp" // ::Cli
#include <map>             // std::map
#include <string>          // std::string

namespace Oanda {
using BaseCli = ::Cli;

class Cli : public BaseCli {
public:
  Cli(int, char **);

private:
  void fetch_quote();
  void quotes_watch();
  void stream_account();
  void tao_bot();

  void execute() override;
};
} // namespace Oanda

#endif
