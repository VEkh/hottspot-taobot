#ifndef DB__HISTORICAL_QUOTE__OANDA_fetch_historical_quotes
#define DB__HISTORICAL_QUOTE__OANDA_fetch_historical_quotes

#include "deps.cpp"            // nlohmann, json
#include "flatten_candles.cpp" // flatten_candles
#include "oanda.h"             // DB::HistoricalQuote::Oanda
#include <string>              // std::string

json DB::HistoricalQuote::Oanda::fetch_historical_quotes() {
  const std::string quotes_resp = this->api_client.fetch_historical_quotes({
      .batch_size = this->batch_size,
      .granularity_seconds = this->granularity_seconds,
      .start_at = this->start_at,
      .symbol = this->symbol,
  });

  try {
    json candles = json::parse(quotes_resp)["candles"];

    return flatten_candles(candles);
  } catch (nlohmann::json_abi_v3_11_2::detail::parse_error &) {
    std::cout << fmt.bold << fmt.red;
    printf("❌ Error parsing json:\n\n%s\n\nRetrying.", quotes_resp.c_str());
    std::cout << fmt.reset << std::endl;

    return R"({})"_json;
  }
}

#endif
