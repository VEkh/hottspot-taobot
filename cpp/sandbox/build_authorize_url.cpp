#include <iostream> // std::cout, std::endl
#include <sstream>  // std::stringstream

int main() {
  // oauth_token=wt0oa6Qkjejv7jnt1WvaYo5HPwXj83KIa3V988h6GSc%3D&oauth_token_secret=xT0EFL6qerkSeYV1BF9a3ZVkd9Wj9V%2FECqSNeyST6Wo%3D&oauth_callback_confirmed=true
  const char *key = "59a8ce75cf8bc55992a77f08cf1930b3";
  const char *oauth_token = "wt0oa6Qkjejv7jnt1WvaYo5HPwXj83KIa3V988h6GSc%3D";

  std::stringstream url_stream;
  url_stream << "https://us.etrade.com/e/t/etws/authorize?"
             << "key=" << key << "&token=" << oauth_token;

  std::cout << url_stream.str() << std::endl;
}
