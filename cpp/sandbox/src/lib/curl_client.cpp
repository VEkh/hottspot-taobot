#if !defined(CURL_CLIENT)
#define CURL_CLIENT

#include "curl_client.h"        // CurlClient, response_t
#include "lib/formatted.cpp"    // Formatted::stream, Formatted::fmt_stream_t
#include "lib/utils/uri.cpp"    // utils::uri::percent_encode
#include "lib/utils/vector.cpp" // utils::vector::join
#include <algorithm>            // std::for_each
#include <iostream>             // std::cout, std::endl
#include <map>                  // std::map
#include <regex>                // std::regex, std::regex_constants, std::smatch
#include <sstream>              // std::stringstream
#include <stdexcept>            // std::invalid_argument
#include <string>               // std::string
#include <utility>              // std::pair
#include <vector>               // std::vector

/*
 * CURL
 * CURLCode
 * CURLOPT_HTTPGET
 * CURLOPT_HTTPHEADER
 * CURLOPT_URL
 * CURLOPT_WRITEDATA
 * CURLOPT_WRITEFUNCTION
 * curl_easy_init
 * curl_easy_perform
 * curl_easy_setopt
 * curl_slist
 * curl_slist_append
 */
#include <curl/curl.h>

CurlClient::CurlClient(props_t props_) {
  props = props_;
  prepare_request();
}

void CurlClient::prepare_request() {
  set_body_params();
  set_debug();
  set_headers();
  set_method();
  set_url();
}

void CurlClient::log_request() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::cout << fmt.bold << fmt.yellow;
  std::cout << std::endl << to_string() << std::endl << std::endl;
  std::cout << fmt.reset;
}

void CurlClient::request() {
  if (props.debug_flag == debug_t::ON) {
    log_request();
    std::cout << stream_format.reset;
  }

  curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)&response);
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, write_response_headers);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
}

// private

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

void CurlClient::set_debug() {
  curl_easy_setopt(curl, CURLOPT_VERBOSE, (long)props.debug_flag);
}

void CurlClient::set_headers() {
  curl_slist *request_headers = NULL;
  std::map<std::string, std::string> headers = props.headers;
  std::map<std::string, std::string>::iterator it;
  std::vector<std::string> header_pairs;

  for (it = headers.begin(); it != headers.end(); it++) {
    std::string header = (it->first + ": " + it->second);

    header_pairs.push_back("-H '" + header + "'");
    request_headers = curl_slist_append(request_headers, header.c_str());
  }

  transformed_props.headers = utils::vector::join(header_pairs, " ");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, request_headers);
}

void CurlClient::set_method() {
  switch (props.method) {
  case http_method_t::GET: {
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    break;
  }
  case http_method_t::POST: {
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    break;
  }
  }

  transformed_props.method = HTTP_METHODS[props.method];
}

void CurlClient::set_url() {
  if (props.url.empty()) {
    throw std::invalid_argument(
        "You must provide a target URL (e.g. https://example.com)");

    return;
  }

  std::string url = props.url + build_query_params();

  transformed_props.url = url;
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
}

std::string CurlClient::to_string() {
  std::vector<std::string> request_parts = {
      "curl",
      "-X" + transformed_props.method,
      transformed_props.headers,
  };

  if (!transformed_props.body_params.empty()) {
    request_parts.push_back("--data '" + transformed_props.body_params + "'");
  }

  request_parts.push_back("\"" + transformed_props.url + "\"");

  std::vector<std::string> filtered_request_parts = utils::vector::filter(
      request_parts, [](std::string part) -> bool { return !part.empty(); });

  return utils::vector::join(filtered_request_parts, " ");
}

size_t CurlClient::write_response(char *buffer, size_t size, size_t data_size,
                                  void *userdata) {
  size_t real_size = size * data_size;
  response_t *res = (response_t *)userdata;

  res->body = buffer;
  res->size = real_size;

  return real_size;
}

std::vector<std::string> CurlClient::extract_header_pair(const char *header) {
  std::regex key_value_regex("(.*):\\s(.*)");
  std::cmatch match;

  std::regex_search(header, match, key_value_regex);

  if (match.size() == 3) {
    return {std::string(match[1]), std::string(match[2])};
  }

  std::regex status_regex(".*http\\/\\d\\.\\d\\s(\\d+).*",
                          std::regex_constants::icase);

  std::regex_search(header, match, status_regex);

  if (match.size() == 2) {
    return {"Status", std::string(match[1])};
  }

  return {};
}

size_t CurlClient::write_response_headers(char *buffer, size_t size,
                                          size_t data_size, void *userdata) {
  size_t real_size = size * data_size;
  response_t *res = (response_t *)userdata;

  std::vector<std::string> pair = extract_header_pair(buffer);

  if (pair.size() == 2) {
    res->headers[pair[0]] = pair[1];
  }

  return real_size;
}
#endif
