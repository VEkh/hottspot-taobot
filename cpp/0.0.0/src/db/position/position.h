#ifndef DB__POSITION_H
#define DB__POSITION_H

#include "lib/pg/pg.cpp" // Pg
#include <string>        // std::string

namespace DB {
class Position {
public:
  struct close_args_t {
    std::string api_key_id;
    double close_order_execution_mid = 0.00;
    std::string close_order_id;
    double close_order_quantity = 0.00;
    double closed_at = 0.00;
    double current_profit = 0.00;
    double max_profit = 0.00;
    double max_profit_at = 0.00;
    std::string open_order_id;
    double stop_loss = 0.00;
    double stop_profit = 0.00;
    bool debug = false;
  };

  struct open_args_t {
    std::string api_key_id;
    double current_profit = 0.00;
    double max_profit = 0.00;
    double max_profit_at = 0.00;
    double open_order_execution_mid = 0.00;
    std::string open_order_id;
    double open_order_quantity = 0.00;
    double opened_at = 0.00;
    double stop_loss = 0.00;
    double stop_profit = 0.00;
    std::string symbol;
    bool debug = false;
  };

  Position(){};
  Position(Pg c) : conn(c){};

  void close(const close_args_t);
  void open(const open_args_t);

private:
  Pg conn;
};
} // namespace DB

#endif
