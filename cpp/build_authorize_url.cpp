#include <iostream> // std::cout, std::endl
#include <sstream>  // std::stringstream

int main() {
  const char *key = "59a8ce75cf8bc55992a77f08cf1930b3";
  const char *oauth_token =
      "snjuWdSRUIkWLPlqA3XNP4rPZ%2FwJtKlYmExp%2B2omUng%3D";

  std::stringstream url_stream;
  url_stream << "https://us.etrade.com/e/t/etws/authorize?"
             << "key=" << key << "&token=" << oauth_token;

  std::cout << url_stream.str() << std::endl;
}
