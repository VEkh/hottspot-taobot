#ifndef ALPACA__MOCK__CLIENT_H
#define ALPACA__MOCK__CLIENT_H

#include "alpaca/types.cpp" // Alpaca::t
#include "types.cpp"        // Global::t
#include <string>           // std::string

namespace Alpaca {
namespace Mock {
class Client {
public:
  using order_action_t = Global::t::order_action_t;
  using order_status_t = Alpaca::t::order_status_t;
  using order_t = Alpaca::t::order_t;
  using quote_t = Global::t::quote_t;

  Client(){};

  std::string fetch_asset();
  std::string fetch_order(const order_t *, const quote_t &);

  void place_order(const long int, order_t *);
};
} // namespace Mock
} // namespace Alpaca

#endif
