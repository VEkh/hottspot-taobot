#ifndef DB__ACCOUNT_STAT_H
#define DB__ACCOUNT_STAT_H

#include "lib/pg/pg.cpp" // Pg

namespace DB {
class AccountStat {
public:
  struct insert_args_t {
    std::string api_key_id;
    double equity = 0.00;
    double margin_buying_power = 0.00;
    double margin_multiplier = 0.00;
  };

  AccountStat(){};
  AccountStat(Pg c) : conn(c){};

  void insert(const insert_args_t);

private:
  Pg conn;
};
} // namespace DB

#endif
