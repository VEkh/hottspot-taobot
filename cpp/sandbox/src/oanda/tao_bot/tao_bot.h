#ifndef OANDA__TAO_BOT_H
#define OANDA__TAO_BOT_H

#include <map>    // std::map
#include <string> // std::string

namespace Oanda {
class TaoBot {
public:
  TaoBot(char *, int, std::map<std::string, std::string> &);

  void run();

private:
  bool FLAG_MARTINGALE = false;
  bool FLAG_NORMALIZE_QUANTITY = false;

  char *symbol;
  int quantity_mulitiplier;
  int quantity;

  void initialize(char *, int, std::map<std::string, std::string> &);
};
} // namespace Oanda

#endif
