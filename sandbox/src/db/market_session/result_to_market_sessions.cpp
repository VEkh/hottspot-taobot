#ifndef DB__MARKET_SESSION_result_to_market_sessions
#define DB__MARKET_SESSION_result_to_market_sessions

#include "lib/utils/string.cpp" // ::utils::string
#include "market_session.h" // DB::MarketSession, query_result_t, market_session_t
#include <list>             // std::list
#include <string>           // std::stod, std::string
#include <vector>           // std::vector

std::list<DB::MarketSession::market_session_t>
DB::MarketSession::result_to_market_sessions(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  std::list<market_session_t> out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");
    market_session_t market_session;

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "close") {
        market_session.close = std::stod(value);
      }

      if (field == "closed_at") {
        market_session.closed_at = std::stod(value);
      }

      if (field == "high") {
        market_session.high = std::stod(value);
      }

      if (field == "id") {
        market_session.id = std::stoi(value);
      }

      if (field == "low") {
        market_session.low = std::stod(value);
      }

      if (field == "open") {
        market_session.open = std::stod(value);
      }

      if (field == "opened_at") {
        market_session.opened_at = std::stod(value);
      }

      if (field == "symbol") {
        market_session.symbol = value;
      }

      if (field == "warm_up_close") {
        market_session.warm_up_close = std::stod(value);
      }

      if (field == "warm_up_closed_at") {
        market_session.warm_up_closed_at = std::stod(value);
      }

      if (field == "warm_up_high") {
        market_session.warm_up_high = std::stod(value);
      }

      if (field == "warm_up_low") {
        market_session.warm_up_low = std::stod(value);
      }

      if (field == "warm_up_open") {
        market_session.warm_up_open = std::stod(value);
      }

      if (field == "warm_up_opened_at") {
        market_session.warm_up_opened_at = std::stod(value);
      }
    }

    out.push_back(market_session);
  }

  return out;
}

#endif
