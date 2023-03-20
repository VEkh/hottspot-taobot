#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp"          // Pg
#include "models/quote/quote.cpp" // DB::Quote
#include <libpq-fe.h>             // PGconn, PQescapeLiteral, PQfreemem
#include <map>                    // std::map
#include <string>                 // std::string

#include "lib/utils/debug.cpp" // ::utils::debug
#include "lib/utils/io.cpp"    // ::utils::io
#include <list>                // std::list
#include <vector>              // std::vector

int main(int argc, char *argv[]) {
  std::list<std::string> args = ::utils::io::extract_args(argc, argv);
  std::list<std::string>::iterator start = args.begin();
  start++;
  std::vector<std::string> args_vec(start, args.end());
  std::map<std::string, std::string> flags =
      ::utils::io::extract_flags(argc, argv);

  if (args.size()) {
    args.pop_front();
  }

  puts("Args Vector: ");
  ::utils::debug::inspect(args_vec);
  puts("");

  puts("Flags: ");
  ::utils::debug::inspect(flags);
}
