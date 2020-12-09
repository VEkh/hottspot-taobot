#include "client/client.cpp"   // ETrade::Client
#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/debug.cpp" // utils::debug
#include <iostream>            // std::cout, std::endl
#include <map>                 // std::map
#include <sstream>             // std::ostringstream
#include <string>              // std::string

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"get_access_token            ", "Get authorization token"},
  };

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::ostringstream message;

  message << fmt.bold << fmt.cyan << "E*TRADE Client Usage:" << std::endl;

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
    ETrade::Client etrade_client;
    etrade_client.get_access_token();

    exit(0);
  }

  Formatted::fmt_stream_t fmt = Formatted::stream();

  std::cout << fmt.bold << fmt.red << "Unknown command <" << command
            << ">. Please refer to usage👇🏾\n"
            << fmt.reset << std::endl;

  print_usage();
  exit(1);
}
