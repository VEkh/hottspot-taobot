#include "td_ameritrade_client.cpp"

int main() {
  TdAmeritradeClient td_ameritrade_client;
  td_ameritrade_client.get_access_token();
  // td_ameritrade_client.refresh_tokens();
  // td_ameritrade_client.get_quote("TSLA");
}
