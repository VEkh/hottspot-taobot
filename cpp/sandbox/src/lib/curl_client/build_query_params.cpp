#if !defined CURL_CLIENT_build_query_params
#define CURL_CLIENT_build_query_params

#include "curl_client.h"        // CurlClient, props, transformed_props
#include "lib/utils/vector.cpp" // utils::vector
#include <map>                  // std::map
#include <string>               // std::string
#include <vector>               // std::vector

std::string CurlClient::build_query_params() {
  std::map<std::string, std::string> params = props.query_params;

  if (params.size() == 0) {
    return "";
  }

  std::vector<std::string> param_pairs;
  std::map<std::string, std::string>::iterator it;

  for (it = params.begin(); it != params.end(); it++) {
    param_pairs.push_back(utils::uri::percent_encode(it->first) + "=" +
                          utils::uri::percent_encode(it->second));
  }

  std::string query_params = utils::vector::join(param_pairs, "&");

  transformed_props.query_params = query_params;
  return "?" + query_params;
}

#endif
