#ifndef ALPACA__CLIENT_read_env_symbols
#define ALPACA__CLIENT_read_env_symbols

#include "client.h"             // Alpaca::Client
#include "deps.cpp"             // json
#include "lib/utils/io.cpp"     // ::utils::io
#include "lib/utils/string.cpp" // ::utils::string
#include <list>                 // std::list
#include <string>               // std::string

std::list<std::string> Alpaca::Client::read_env_symbols(json &config) {
  std::list<std::string> formatted_symbols;
  std::list<std::string> symbols = config["env_symbols"];

  for (const std::string symbol : symbols) {
    formatted_symbols.push_back(::utils::string::upcase(symbol));
  }

  return formatted_symbols;
}

#endif
