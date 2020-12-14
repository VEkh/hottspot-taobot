#if !defined CURL_CLIENT_set_body_params
#define CURL_CLIENT_set_body_params

#include "curl_client.h"        // CurlClient, curl, props, transformed_props
#include "lib/utils/uri.cpp"    // utils::uri
#include "lib/utils/vector.cpp" // utils::vector
#include <algorithm>            // std::for_each
#include <curl/curl.h> // CURLOPT_POSTFIELDS, CURLOPT_POSTFIELDSIZE, curl_easy_setopt
#include <map>         // std::map
#include <string>      // std::string
#include <utility> // std::pair
#include <vector>  // std::vector

void CurlClient::set_body_params() {
  std::string params_string = props.body;

  std::map<std::string, std::string> body_params = props.body_params;

  if (params_string.empty() && body_params.empty()) {
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

    params_string = utils::vector::join(param_pairs, "&");
  }

  transformed_props.body_params = params_string;
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, params_string.size());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS,
                   transformed_props.body_params.c_str());
}

#endif
