#ifndef DB__HISTORICAL_QUOTE__OANDA_H
#define DB__HISTORICAL_QUOTE__OANDA_H

#include "db/historical_quote/base/base.cpp" // DB::HistoricalQuote::Base, init_args_t, quote_t
#include "deps.cpp"                          // json
#include "oanda/client/client.cpp" // ::Oanda::Client

namespace DB {
namespace HistoricalQuote {
using Base = DB::HistoricalQuote::Base;

class Oanda : public Base {
public:
  Oanda(){};
  Oanda(const init_args_t);

private:
  ::Oanda::Client api_client;
  int granularity_seconds = 5;

  json fetch_historical_quotes() override;
  json flatten_candles(json &);

  quote_t prepare_for_upsert(json &) override;
};
} // namespace HistoricalQuote
} // namespace DB

#endif
