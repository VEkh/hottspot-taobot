#if !defined(CURL_CLIENT)
#define CURL_CLIENT

#include "curl_client.h"
#include "utils/debugger.cpp" // utils::debugger::inspect
#include "utils/uri.cpp"      // utils::uri::percentEncode
#include "utils/vector.cpp"   // utils::vector::join
#include <algorithm>          // std::for_each
#include <map>                // std::map
#include <sstream>            // std::stringstream
#include <stdexcept>          // std::invalid_argument
#include <string>             // std::string
#include <utility>            // std::pair
#include <vector>             // std::vector

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

void CurlClient::print_request() {
  utils::debugger::inspect("\n===========================================\n\n" +
                           to_string() +
                           "\n\n===========================================\n");
}

void CurlClient::request() {
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
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
    param_pairs.push_back(utils::uri::percentEncode(it->first) + "=" +
                          utils::uri::percentEncode(it->second));
  }

  std::string query_params = utils::vector::join(param_pairs, "&");

  transformed_props.query_params = query_params;
  return "?" + query_params;
}

void CurlClient::set_body_params() {
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

  std::string params_string = utils::vector::join(param_pairs, "&");

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

    header_pairs.push_back("-H \"" + header + "\"");
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
    request_parts.push_back("--data \"" + transformed_props.body_params + "\"");
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
#endif
