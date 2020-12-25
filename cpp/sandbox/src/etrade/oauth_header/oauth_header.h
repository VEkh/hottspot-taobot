#if !defined ETRADE__OAUTH_HEADER_H
#define ETRADE__OAUTH_HEADER_H

#include "lib/curl_client/curl_client.h" // CurlClient
#include <ctime>                         // std::time
#include <map>                           // std::map
#include <string>                        // std::string

namespace ETrade {
class OAuthHeader {
public:
  struct props_t {
    CurlClient::http_method_t method;
    std::map<std::string, std::string> params;
    std::string request_url;
  };

  OAuthHeader(){};
  OAuthHeader(props_t);
  std::string build();
  std::string compute_nonce();

private:
  props_t props;
  std::map<std::string, std::string> params;
  std::string nonce;
  std::time_t timestamp = std::time(nullptr);

  std::string build_params_string();
  std::string build_signature();
  std::string build_signature_base_string();
};
} // namespace ETrade

#endif
