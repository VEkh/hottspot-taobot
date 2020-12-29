#if !defined ETRADE__STRADDLE_fetch_order_status
#define ETRADE__STRADDLE_fetch_order_status

#include "lib/curl_client/curl_client.h" // CurlClient
#include "straddle.h" // ETrade::Straddle, etrade_client, order_t

const char *ETrade::Straddle::fetch_order_status(order_t order) {
  CurlClient curl_client = etrade_client.fetch(
      etrade_client.client_config.base_url + "/v1/accounts/");
}

#endif
