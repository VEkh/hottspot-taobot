#include "lib/formatted.cpp"                         // Formatted
#include "lib/pg/pg.cpp"                             // Pg
#include "lib/utils/io.cpp"                          // utils::io
#include "performance_logger/performance_logger.cpp" // Alpaca::PerformanceLogger
#include "quote/quote.cpp"                           // DB::Quote
#include "quote/quote.cpp"                           // Alpaca::Quote
#include "tao_bot/tao_bot.cpp"                       // Alpaca::TaoBot
#include <iostream>                                  // std::cout, std::endl
#include <list>                                      // std::list
#include <map>                                       // std::map
#include <sstream>                                   // std::ostringstream
#include <stdexcept>                                 // std::invalid_argument
#include <stdio.h>                                   // printf
#include <string>                                    // std::string
#include <vector>                                    // std::vector

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"quotes_watch_avg_one_sec_variances <SYMBOLS>       ",
       "Periodically update quote average one sec variances"},
  };

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::ostringstream message;

  message << fmt.bold << fmt.cyan << "Models Client Usage:" << std::endl;

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
  args.pop_front(); // Remove `tao_bot` arg

  std::list<std::string> upcased_args =
      ::utils::io::extract_args(argc, argv, ::utils::string::upcase);
  upcased_args.pop_front(); // Remove `tao_bot` arg

  std::map<std::string, std::string> flags =
      ::utils::io::extract_flags(argc, argv);

  if (command == "quotes_watch_avg_one_sec_variances") {
    Pg pg(flags);
    pg.connect();

    DB::Quote db_quote(pg);
    db_quote.watch_avg_one_sec_variances(upcased_args);

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
