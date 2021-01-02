#include "etrade/straddle/straddle.h"
#include "lib/utils/debug.cpp"
#include <iostream>
#include <string>

ETrade::Straddle::order_status_t string_to_enum(const std::string &in) {
  char const *const *statuses = ETrade::Straddle::ORDER_STATUSES;
  int length = sizeof(ETrade::Straddle::ORDER_STATUSES) /
               sizeof(*ETrade::Straddle::ORDER_STATUSES);

  for (int i = 0; i < length; i++) {
    if (statuses[i] == in) {
      return (ETrade::Straddle::order_status_t)i;
    }
  }

  Formatted::fmt_stream_t fmt = Formatted::stream();

  std::cout << fmt.bold << fmt.red;
  std::cout << "❌ Status <" << in << "> was not present in ORDER_STATUSES."
            << std::endl;
  std::cout << fmt.reset;

  exit(1);
}

int main() { std::cout << string_to_enum("OPEN") << std::endl; }
