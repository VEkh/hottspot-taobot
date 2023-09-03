#include "db/quote/quote.cpp" // DB::Quote
#include "lib/formatted.cpp"  // Formatted
#include "lib/pg/pg.cpp"      // Pg
#include "lib/utils/io.cpp"   // utils::io
#include <iostream>           // std::cout, std::endl
#include <list>               // std::list
#include <map>                // std::map
#include <sstream>            // std::ostringstream
#include <stdexcept>          // std::invalid_argument
#include <stdio.h>            // printf
#include <string>             // std::string

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"quote:upsert_all_avg_one_sec_variances <SYMBOL> <OPTS> ",
       "Retroactively upsert a symbol's average one second variances"},
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

  std::list<std::string> args = ::utils::io::extract_args(argc, argv);
  args.pop_front(); // Remove command arg

  std::list<std::string> upcased_args =
      ::utils::io::extract_args(argc, argv, ::utils::string::upcase);
  upcased_args.pop_front(); // Remove command arg

  std::map<std::string, std::string> flags =
      ::utils::io::extract_flags(argc, argv);

  if (command == "quote:upsert_all_avg_one_sec_variances") {
    if (upcased_args.empty()) {
      std::string message =
          Formatted::error_message("Please provide at least one symbol.");

      throw std::invalid_argument(message);
    }

    Pg pg(flags);
    pg.connect();

    DB::Quote db_quote(pg);
    db_quote.upsert_all_avg_one_sec_variances({
        .starting_from = flags["starting-from"],
        .symbol = upcased_args.front(),
    });

    pg.disconnect();

    exit(0);
  }

  std::cout << fmt.bold << fmt.red;
  printf("Unknown command <%s>. Please refer to usage👇🏾\n\n",
         command.c_str());
  std::cout << fmt.reset;

  print_usage();
  exit(127);
}
