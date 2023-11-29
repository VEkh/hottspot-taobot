#ifndef DB__POSITION_H
#define DB__POSITION_H

#include "lib/pg/pg.cpp" // Pg
#include "types.cpp"     // Global::t
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
    double min_profit = 0.00;
    double min_profit_at = 0.00;
    std::string open_order_id;
    double stop_loss = 0.00;
    double stop_profit = 0.00;
    // Optional
    bool debug = false;
  };

  struct compute_golden_ratio_args_t {
    std::string api_key;
    bool debug = false;
    int limit = 0;
    bool log_positions = false;
    std::string project;
    std::string symbol;
  };

  struct get_golden_ratio_positions_args_t {
    std::string api_key_id;
    bool debug = false;
    int limit = 0;
    std::string symbol;
  };

  struct open_args_t {
    std::string api_key_id;
    double current_profit = 0.00;
    double max_profit = 0.00;
    double max_profit_at = 0.00;
    double min_profit = 0.00;
    double min_profit_at = 0.00;
    double open_order_execution_mid = 0.00;
    std::string open_order_id;
    double open_order_quantity = 0.00;
    double opened_at = 0.00;
    double stop_loss = 0.00;
    double stop_profit = 0.00;
    std::string symbol;
    // Optional
    bool debug = false;
  };

  Position(){};
  Position(Pg c) : conn(c){};

  void close(const close_args_t);
  void compute_golden_stop_ratio(const compute_golden_ratio_args_t);
  void open(const open_args_t);

private:
  using avg_one_sec_variances_t = Global::t::avg_one_sec_variances_t;
  using query_result_t = Pg::query_result_t;

  struct position_t {
    double closed_at;
    double current_profit;
    double max_profit;
    double max_profit_at;
    double min_profit;
    double min_profit_at;
    double opened_at;
    std::string symbol;
  };

  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg conn;

  std::list<position_t>
  get_golden_ratio_positions(const get_golden_ratio_positions_args_t);

  std::list<position_t> result_to_positions(const query_result_t &);
};
} // namespace DB

#endif
