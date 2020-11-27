#include "libraries.cpp"
#include "td_ameritrade_client.cpp" // TdAmeritradeClient
#include "utils/formatted.cpp"      // Formatted
#include <iostream>                 // std::cout, std::endl
#include <map>                      // std::map
#include <sstream>                  // std::ostringstream
#include <string>                   // std::string

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"get_access_token            ", "Get authorization tokens"},
      {"get_quote <SYMBOL>          ", "Get quote for the given symbol"},
      {"refresh_tokens              ", "Refresh authorization tokens"},
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
  TdAmeritradeClient td_ameritrade_client;

  if (command == "get_access_token") {
    td_ameritrade_client.get_access_token();
  } else if (command == "get_quote") {
    char *symbol = argc < 3 ? nullptr : argv[2];
    td_ameritrade_client.get_quote(symbol);
  } else if (command == "refresh_tokens") {
    td_ameritrade_client.refresh_tokens();
  } else {
    Formatted::fmt_stream_t fmt = Formatted::stream();

    std::cout << fmt.bold << fmt.red << "Unknown command <" << command
              << ">. Please refer to usage👇🏾\n"
              << fmt.reset << std::endl;

    print_usage();
    exit(1);
  }
}
