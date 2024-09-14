#ifndef OANDA__CLIENT_fetch_historical_quotes
#define OANDA__CLIENT_fetch_historical_quotes

#include "client.h"  // Oanda::Client, fetch_historical_quotes_args_t
#include "fetch.cpp" // fetch
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include "lib/utils/time.cpp"                     // ::utils::time_
#include <algorithm>                              // std::min
#include <string>                                 // std::string, std::to_string

namespace Oanda {
namespace fetch_historical_quotes {
bool is_retriable_response(const CurlClient &curl_client) {
  const std::string response_body = curl_client.response.body;

  return response_body.empty();
}
} // namespace fetch_historical_quotes
} // namespace Oanda

std::string Oanda::Client::fetch_historical_quotes(
    const fetch_historical_quotes_args_t args) {
  std::string request_url =
      config.base_url + "/v3/instruments/" + args.symbol + "/candles";

  const int batch_size = std::min(args.batch_size, 5000);

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient {
        return fetch({
            .query_params =
                {
                    {"count", std::to_string(batch_size)},
                    {"from", ::utils::time_::date_string(
                                 args.start_at, "%FT%H:%M:%SZ", "UTC")},
                    {"granularity",
                     "S" + std::to_string(args.granularity_seconds)},
                    {"price", "BAM"},
                },
            .timeout_seconds = 3,
            .url = request_url,
        });
      },
      Oanda::fetch_historical_quotes::is_retriable_response);

  return curl_client.response.body;
}

#endif
