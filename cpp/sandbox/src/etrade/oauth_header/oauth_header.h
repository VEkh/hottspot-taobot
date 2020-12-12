#if !defined ETRADE__OAUTH_HEADER_H
#define ETRADE__OAUTH_HEADER_H

#include <ctime>  // std::time
#include <map>    // std::map
#include <string> // std::string

namespace ETrade {
class OAuthHeader {
public:
  struct props_t {
    std::map<std::string, std::string> params;
    std::string request_url;
  };

  OAuthHeader(props_t);
  std::string build();

private:
  props_t props;
  std::map<std::string, std::string> params;
  std::string nonce = compute_nonce();
  std::time_t timestamp = std::time(nullptr);

  std::string build_params_string();
  std::string build_signature();
  std::string build_signature_base_string();
  std::string compute_nonce();
};
} // namespace ETrade

#endif
