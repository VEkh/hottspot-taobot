#include "td_ameritrade_client.cpp" // TdAmeritradeClient
#include <iostream>                 // std::cout, std::endl
#include <string>                   // std::string

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "TDAmeritrade Client Usage: " << std::endl
              << "get_access_token -- Get authorization tokens\n"
              << "get_quote <SYMBOL> -- Get quote for the given symbol\n"
              << "refresh_tokens -- Refresh authorization tokens " << std::endl;

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
  }
}
