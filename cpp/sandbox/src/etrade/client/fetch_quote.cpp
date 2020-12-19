#if !defined ETRADE__CLIENT_fetch_quote
#define ETRADE__CLIENT_fetch_quote

#include "client.h"                        // ETrade::Client, tokens
#include "etrade/deps.cpp"                 // json, xmlpp::DomParser
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted::error_message
#include "load_token.cpp"                  // load_token
#include <iostream>                        // std::cout, std::endl
#include <map>                             // std::map
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::stod, std::string

bool is_valid_response(xmlpp::Element *document) {
  return !(document->find("//QuoteData//All").empty());
}

void terminate(std::string response_body, std::string symbol) {
  Formatted::fmt_stream_t fmt = Formatted::stream();

  std::cout << fmt.bold << fmt.red << std::endl;
  std::cout << "❌ There was a problem fetching <" << symbol
            << ">'s quote. Here's the response:" << std::endl;
  std::cout << response_body << std::endl;
  std::cout << fmt.reset;

  exit(1);
}

// TODO: Move to straddle
std::string xml_to_json(xmlpp::Element *document, std::string symbol) {
  xmlpp::Node *current_price_node =
      document->find("//QuoteData//All//lastTrade").at(0)->get_first_child();

  xmlpp::Node *high_price_node =
      document->find("//QuoteData//All//high").at(0)->get_first_child();

  xmlpp::Node *low_price_node =
      document->find("//QuoteData//All//low").at(0)->get_first_child();

  xmlpp::ContentNode *current_price_content =
      dynamic_cast<xmlpp::ContentNode *>(current_price_node);

  xmlpp::ContentNode *high_price_content =
      dynamic_cast<xmlpp::ContentNode *>(high_price_node);

  xmlpp::ContentNode *low_price_content =
      dynamic_cast<xmlpp::ContentNode *>(low_price_node);

  json output;

  std::map<std::string, double> quote = {
      {"highPrice", std::stod(high_price_content->get_content())},
      {"lastPrice", std::stod(current_price_content->get_content())},
      {"lowPrice", std::stod(low_price_content->get_content())},
  };

  output[symbol] = quote;

  return output.dump(2);
}

std::string ETrade::Client::fetch_quote(char *symbol) {
  if (symbol == nullptr) {
    std::string error_message =
        Formatted::error_message("Please provide a stock symbol");

    throw std::invalid_argument(error_message);
  }

  return fetch_quote(std::string(symbol));
}

std::string ETrade::Client::fetch_quote(std::string symbol) {
  load_token();
  std::string request_url = "https://api.etrade.com/v1/market/quote/" + symbol;

  std::string request_header = build_request_header(
      request_url, {
                       {"oauth_token", oauth.token},
                       {"oauth_token_secret", oauth.token_secret},
                   });

  CurlClient::props_t curl_props = {
      .body = "",
      .body_params = {},
      .debug_flag = (CurlClient::debug_t)props.debug_flag,
      .headers = {{"Authorization", request_header}},
      .method = CurlClient::http_method_t::GET,
      .query_params = {},
      .url = request_url,
  };

  CurlClient curl_client(curl_props);
  curl_client.request();

  std::string response_body = curl_client.response.body;

  xmlpp::DomParser parser;
  parser.parse_memory(response_body);
  xmlpp::Element *document = parser.get_document()->get_root_node();

  if (!is_valid_response(document)) {
    terminate(response_body, symbol);
  }

  return response_body;
}

#endif
