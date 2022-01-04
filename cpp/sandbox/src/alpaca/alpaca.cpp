#include "client/client.cpp" // Alpaca::Client
#include "lib/formatted.cpp" // Formatted
#include <iostream>          // std::cout, std::endl
#include <map>               // std::map
#include <sstream>           // std::ostringstream
#include <stdio.h>           // printf
#include <string>            // std::string

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"fetch_quote <SYMBOL>         ", "Get quote for the given symbol"},
      {"tao_bot <SYMBOL> <QUANTITY>",
       "Launch trading bot for the given currency pair"},
  };

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::ostringstream message;

  message << fmt.bold << fmt.cyan << "Alpaca Client Usage:" << std::endl;

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

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::string command = argv[1];

  if (command == "fetch_quote") {
    Alpaca::Client alpaca_client;
    char *symbol = argc < 3 ? nullptr : argv[2];

    std::string quote = alpaca_client.fetch_quote(symbol);
    puts(quote.c_str());

    exit(0);
  }

  std::cout << fmt.bold << fmt.red;
  printf("Unknown command <%s>. Please refer to usage👇🏾\n\n",
         command.c_str());
  std::cout << fmt.reset;

  print_usage();
  exit(127);
}
