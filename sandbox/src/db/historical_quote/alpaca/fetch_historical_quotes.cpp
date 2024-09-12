#ifndef DB__HISTORICAL_QUOTE__ALPACA_fetch_historical_quotes
#define DB__HISTORICAL_QUOTE__ALPACA_fetch_historical_quotes

#include "alpaca.h" // DB::HistoricalQuote::Alpaca
#include "deps.cpp" // nlohmann, json
#include <string>   // std::string

json DB::HistoricalQuote::Alpaca::fetch_historical_quotes() {
  const std::string quotes_resp = this->api_client.fetch_historical_quotes({
      .batch_size = this->batch_size,
      .end_at = this->end_at,
      .start_at = this->start_at,
      .symbol = this->symbol,
  });

  try {
    return json::parse(quotes_resp)["quotes"][this->symbol];
  } catch (nlohmann::json_abi_v3_11_2::detail::parse_error &) {
    std::cout << fmt.bold << fmt.red;
    printf("❌ Error parsing json:\n\n%s\n\nRetrying.", quotes_resp.c_str());
    std::cout << fmt.reset << std::endl;

    return R"({})"_json;
  }
}

#endif
