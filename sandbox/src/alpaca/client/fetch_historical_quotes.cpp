#ifndef ALPACA__CLIENT_fetch_historical_quotes
#define ALPACA__CLIENT_fetch_historical_quotes

#include "client.h"  // Alpaca::Client, fetch_historical_quotes_args_t
#include "fetch.cpp" // fetch
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include "lib/utils/time.cpp"                     // ::utils::time_
#include <string>                                 // std::string, std::to_string

namespace Alpaca {
namespace fetch_historical_quotes {
bool is_retriable_response(const CurlClient &curl_client) {
  const std::string response_body = curl_client.response.body;

  return response_body.empty();
}
} // namespace fetch_historical_quotes
} // namespace Alpaca

std::string Alpaca::Client::fetch_historical_quotes(
    const fetch_historical_quotes_args_t args) {
  std::string request_url = config.data_base_url + "/v2/stocks/quotes";

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient {
        return fetch({
            .query_params =
                {
                    {"end", ::utils::time_::date_string(args.end_at,
                                                        "%FT%H:%M:%SZ", "UTC")},
                    {"feed", "sip"},
                    {"limit", std::to_string(args.batch_size)},
                    {"sort", "asc"},
                    {"start", ::utils::time_::date_string(
                                  args.start_at, "%FT%H:%M:%SZ", "UTC")},
                    {"symbols", args.symbol},
                },
            .timeout_seconds = 3,
            .url = request_url,
        });
      },
      Alpaca::fetch_historical_quotes::is_retriable_response);

  return curl_client.response.body;
}

#endif
