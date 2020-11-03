#include <iostream> // std::cout, std::endl
#include <sstream>  // std::stringstream

int main() {
  const char *key = "";
  const char *oauth_token = "";

  std::stringstream url_stream;
  url_stream << "https://us.etrade.com/e/t/etws/authorize?"
             << "key=" << key << "&token=" << oauth_token;

  std::cout << url_stream.str() << std::endl;
}
