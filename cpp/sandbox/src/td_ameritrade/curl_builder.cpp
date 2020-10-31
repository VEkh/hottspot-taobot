#include "curl_builder.h"
#include "../utils/debugger.cpp" // utils::debugger::inspect
#include "../utils/uri.cpp"      // utils::uri::percentEncode
#include "../utils/vector.cpp"   // utils::vector::join
#include <algorithm>             // std::for_each
#include <map>                   // std::map
#include <sstream>               // std::stringstream
#include <stdexcept>             // std::invalid_argument
#include <string>                // std::string
#include <utility>               // std::pair
#include <vector>                // std::vector

std::string CurlBuilder::build() {
  init_request();
  set_body_params();
  set_headers();
  set_query_params();
  compose();

  return output.str();
}

void CurlBuilder::init_request() {
  if (props.method.empty()) {
    throw std::invalid_argument(
        "You must provide a request method (e.g. GET, POST, PATCH, DELETE)");

    return;
  }

  if (props.url.empty()) {
    throw std::invalid_argument(
        "You must provide a target URL (e.g. https://example.com)");

    return;
  }

  request.method = "-X" + props.method;
  request.url = props.url;
}

void CurlBuilder::compose() {
  std::vector<std::string> request_parts = {
      "curl",
      request.method,
      request.headers,
      "\"" + request.url + "\"",
      request.body_params,
  };

  std::vector<std::string> filtered_request_parts = utils::vector::filter(
      request_parts, [](std::string part) -> bool { return !part.empty(); });

  output << utils::vector::join(filtered_request_parts, " ");
}

void CurlBuilder::set_body_params() {
  std::map<std::string, std::string> params = props.body_params;

  if (params.size() == 0) {
    return;
  }

  std::vector<std::string> param_pairs;

  std::for_each(params.begin(), params.end(),
                [&](std::pair<std::string, std::string> param) -> void {
                  param_pairs.push_back(
                      utils::uri::percentEncode(param.first) + "=" +
                      utils::uri::percentEncode(param.second));
                });

  request.body_params =
      "--data \"" + utils::vector::join(param_pairs, "&") + "\"";
}

void CurlBuilder::set_query_params() {
  std::map<std::string, std::string> params = props.query_params;

  if (params.size() == 0) {
    return;
  }

  std::vector<std::string> param_pairs;

  std::map<std::string, std::string>::iterator it;

  for (it = params.begin(); it != params.end(); it++) {
    param_pairs.push_back(utils::uri::percentEncode(it->first) + "=" +
                          utils::uri::percentEncode(it->second));
  }

  request.url += "?" + utils::vector::join(param_pairs, "&");
}

void CurlBuilder::set_headers() {
  std::map<std::string, std::string> headers = props.headers;

  std::vector<std::string> header_pairs;

  std::map<std::string, std::string>::iterator it;
  for (it = headers.begin(); it != headers.end(); it++) {
    header_pairs.push_back("-H \"" + it->first + ": " + it->second + "\"");
  }

  request.headers += utils::vector::join(header_pairs, " ");
}
