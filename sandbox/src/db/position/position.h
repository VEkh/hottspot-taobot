#ifndef DB__POSITION_H
#define DB__POSITION_H

#include "lib/pg/pg.cpp" // Pg
#include "types.cpp"     // Global::t
#include <list>          // std::list
#include <string>        // std::string

namespace DB {
class Position {
public:
  struct close_args_t {
    std::string api_key_id;
    double close_order_execution_price = 0.00;
    std::string close_order_id;
    double close_order_quantity = 0.00;
    double closed_at = 0.00;
    double current_profit = 0.00;
    bool debug = false;
    double max_profit = 0.00;
    double max_profit_at = 0.00;
    double min_profit = 0.00;
    double min_profit_at = 0.00;
    std::string open_order_id;
    double stop_loss = 0.00;
    double stop_profit = 0.00;
    double to_account_currency_ratio = 1.00;
  };

  struct get_closed_positions_args_t {
    std::string api_key_id;
    bool debug = false;
    double market_open_epoch = 0;
    std::string symbol;
  };

  struct get_net_return_positions_args_t {
    std::string api_key_id;
    bool debug = false;
    std::string end_at;
    int limit = 0;
    std::string start_at;
    std::string symbol;
  };

  struct net_return_args_t {
    std::string api_key;
    bool debug = false;
    std::string end_at;
    int limit = 0;
    bool log_positions = false;
    std::string project;
    std::string start_at;
    std::string symbol;
  };

  struct open_args_t {
    std::string account_currency = "USD";
    std::string api_key_id;
    std::string currency = "USD";
    double current_profit = 0.00;
    bool debug = false;
    double max_profit = 0.00;
    double max_profit_at = 0.00;
    double min_profit = 0.00;
    double min_profit_at = 0.00;
    double open_order_execution_price = 0.00;
    std::string open_order_id;
    double open_order_quantity = 0.00;
    double opened_at = 0.00;
    double stop_loss = 0.00;
    double stop_profit = 0.00;
    std::string symbol;
    double to_account_currency_ratio = 1.00;
  };

  struct position_t {
    std::string account_currency;
    double close_order_quantity;
    double close_order_execution_price;
    double closed_at;
    std::string close_order_id;
    std::string currency;
    double current_profit;
    double max_position_profit;
    double max_profit;
    double max_profit_at;
    double min_profit;
    double min_profit_at;
    double open_order_execution_price;
    double open_order_quantity;
    double opened_at;
    std::string open_order_id;
    double stop_loss;
    double stop_profit;
    std::string symbol;
    double to_account_currency_ratio;
  };

  Position(){};
  Position(Pg c) : conn(c){};

  std::list<position_t> get_closed_positions(const get_closed_positions_args_t);

  void close(const close_args_t);
  void net_return(const net_return_args_t);
  void open(const open_args_t);

private:
  using query_result_t = Pg::query_result_t;

  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg conn;

  std::list<position_t>
  get_net_return_positions(const get_net_return_positions_args_t);

  std::list<position_t> result_to_positions(const query_result_t &);
};
} // namespace DB

#endif
