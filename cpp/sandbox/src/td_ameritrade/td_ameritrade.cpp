#include "td_ameritrade_client.cpp"   // TdAmeritradeClient
#include "utils/stream_formatter.cpp" // StreamFormatter, StreamFormatter::code_t
#include <iostream>                   // std::cout, std::endl
#include <stdexcept>                  // std::invalid_argument
#include <string>                     // std::string

int main(int argc, char *argv[]) {
  TdAmeritradeClient td_ameritrade_client;
  std::string command = argc > 1 ? argv[1] : "";

  if (command == "get_access_token") {
    td_ameritrade_client.get_access_token();
  } else if (command == "get_quote") {
    if (argc < 3) {
      throw std::invalid_argument("Please provide a stock symbol");
    }

    td_ameritrade_client.get_quote(std::string(argv[2]));
  } else if (command == "refresh_tokens") {
    td_ameritrade_client.refresh_tokens();
  } else {
    std::cout << "TDAmeritrade Client Usage: " << std::endl
              << "get_access_token -- Get authorization tokens\n"
              << "get_quote <SYMBOL> -- Get quote for the given symbol\n"
              << "refresh_tokens -- Refresh authorization tokens " << std::endl;
  }
}
