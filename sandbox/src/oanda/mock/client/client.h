#ifndef OANDA__MOCK__CLIENT_H
#define OANDA__MOCK__CLIENT_H

#include "oanda/types.cpp" // Oanda::t
#include "types.cpp"       // Global::t
#include <string>          // std::string

namespace Oanda {
namespace Mock {
class Client {
public:
  using order_action_t = Global::t::order_action_t;
  using order_status_t = Oanda::t::order_status_t;
  using order_t = Oanda::t::order_t;

  Client(){};

  std::string fetch_order(const long int);

  void place_order(const long int, order_t *);
};
} // namespace Mock
} // namespace Oanda

#endif
