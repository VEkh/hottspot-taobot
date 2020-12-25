#if !defined CURL_CLIENT_set_request_body
#define CURL_CLIENT_set_request_body

#include "curl_client.h"        // CurlClient, curl, props, transformed_props
#include "lib/utils/uri.cpp"    // utils::uri
#include "lib/utils/vector.cpp" // utils::vector
#include <algorithm>            // std::for_each
#include <curl/curl.h> // CURLOPT_POSTFIELDS, CURLOPT_POSTFIELDSIZE, curl_easy_setopt
#include <map>         // std::map
#include <string>      // std::string
#include <utility> // std::pair
#include <vector>  // std::vector

void CurlClient::set_request_body() {
  std::string body = props.body;

  std::map<std::string, std::string> body_params = props.body_params;

  if (body.empty() && body_params.empty()) {
    return;
  }

  if (!body_params.empty()) {
    std::vector<std::string> param_pairs;

    std::for_each(body_params.begin(), body_params.end(),
                  [&](std::pair<std::string, std::string> param) -> void {
                    param_pairs.push_back(
                        utils::uri::percent_encode(param.first) + "=" +
                        utils::uri::percent_encode(param.second));
                  });

    body = utils::vector::join(param_pairs, "&");
  }

  transformed_props.body = body;
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.size());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, transformed_props.body.c_str());
}

#endif
