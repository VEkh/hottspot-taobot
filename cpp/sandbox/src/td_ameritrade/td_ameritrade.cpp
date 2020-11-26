#include "td_ameritrade_client.cpp"

#include <iostream> // std::cout, std::endl
#include <string>

int main(int argc, char *argv[]) {
  TdAmeritradeClient td_ameritrade_client;
  std::string command = argc > 1 ? argv[1] : "";

  if (command == "get_access_token") {
    td_ameritrade_client.get_access_token();
  } else if (command == "get_quote") {
    td_ameritrade_client.get_quote("TSLA");
  } else if (command == "refresh_tokens") {
    td_ameritrade_client.refresh_tokens();
  } else {
    std::cout << "TDAmeritrade Client Usage..." << std::endl;
  }
}
