#ifndef OANDA__CLIENT_map_margin_rates
#define OANDA__CLIENT_map_margin_rates

#include "client.h" // Oanda::Client:
#include "deps.cpp" // json
#include <map>      // std::map
#include <string>   // std::string

std::map<std::string, std::string>
Oanda::Client::map_margin_rates(json instruments_json) {
  std::map<std::string, std::string> out;

  for (json::iterator it = instruments_json.begin();
       it != instruments_json.end(); it++) {
    out[it.key()] = it.value()["marginRate"];
  }

  return out;
}

#endif
