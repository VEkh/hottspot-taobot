#include "client/client.cpp"     // TdAmeritrade::Client
#include "lib/formatted.cpp"     // Formatted
#include "straddle/straddle.cpp" // TdAmeritrade::Straddle
#include "utils/debug.cpp"       // utils::debug
#include <iostream>              // std::cout, std::endl
#include <map>                   // std::map
#include <sstream>               // std::ostringstream
#include <stdlib.h>              // strtol
#include <string>                // std::string

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"get_access_token            ", "Get authorization tokens"},
      {"get_quote <SYMBOL>          ", "Get quote for the given symbol"},
      {"manual_straddle <SYMBOL>    ",
       "Return straddle prices for manual entry"},
      {"refresh_tokens              ", "Refresh authorization tokens"},
      {"straddle <SYMBOL> <QUANTITY>",
       "Launch straddle strategy for the given symbol"},
  };

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::ostringstream message;

  message << fmt.bold << fmt.cyan << "TDAmeritrade Client Usage:" << std::endl;

  std::map<std::string, const char *>::iterator it;
  for (it = commands.begin(); it != commands.end(); ++it) {
    message << fmt.bold << fmt.yellow << it->first << fmt.reset << " | "
            << it->second << std::endl;
  }

  std::cout << message.str();
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage();
    exit(1);
  }

  std::string command = argv[1];

  if (command == "get_access_token") {
    TdAmeritrade::Client td_ameritrade_client;
    td_ameritrade_client.get_access_token();

    exit(0);
  }

  if (command == "get_quote") {
    TdAmeritrade::Client td_ameritrade_client;
    char *symbol = argc < 3 ? nullptr : argv[2];

    std::string quote = td_ameritrade_client.get_quote(symbol);
    std::cout << quote;

    exit(0);
  }

  if (command == "manual_straddle") {
    char *symbol = argc < 3 ? nullptr : argv[2];
    TdAmeritrade::Straddle straddle = TdAmeritrade::Straddle(symbol);
    straddle.manual_run();

    exit(0);
  }

  if (command == "refresh_tokens") {
    TdAmeritrade::Client td_ameritrade_client;
    td_ameritrade_client.refresh_tokens();

    exit(0);
  }

  if (command == "straddle") {
    char *symbol = argc < 3 ? nullptr : argv[2];
    int quantity = argc < 4 ? 0 : strtol(argv[3], nullptr, 10);

    TdAmeritrade::Straddle straddle = TdAmeritrade::Straddle(symbol, quantity);
    straddle.run();

    exit(0);
  }

  Formatted::fmt_stream_t fmt = Formatted::stream();

  std::cout << fmt.bold << fmt.red << "Unknown command <" << command
            << ">. Please refer to usage👇🏾\n"
            << fmt.reset << std::endl;

  print_usage();
  exit(1);
}
