#ifndef ALPACA__TAO_BOT_log_momentum_reversals
#define ALPACA__TAO_BOT_log_momentum_reversals

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot, fmt, quote_t
#include <map>                // std::map

void Alpaca::TaoBot::log_momentum_reversals() {
  void (*log_reversals)(std::map<std::string, quote_t> &, const char *) =
      [](std::map<std::string, quote_t> &reversals, const char *label) -> void {
    Formatted::fmt_stream_t fmt = Formatted::stream();

    std::cout << fmt.underline;
    printf("%s:\n", label);
    std::cout << fmt.no_underline;

    for (std::map<std::string, quote_t>::iterator it = reversals.begin();
         it != reversals.end(); it++) {
      if (it != reversals.begin()) {
        printf(" • ");
      }

      const quote_t quote = it->second;

      printf("%.2f @ %s", quote.price,
             ::utils::time_::date_string(quote.timestamp / 1000, "%R",
                                         "America/Chicago")
                 .c_str());
    }

    std::cout << std::endl << std::endl;
  };

  std::cout << fmt.bold << fmt.cyan;
  log_reversals(this->momentum_reversals["resistance"], "📉 Resistance Points");
  std::cout << fmt.reset;

  std::cout << fmt.cyan;
  log_reversals(this->momentum_reversals["support"], "📈 Support Points");
  std::cout << fmt.reset;
}

#endif
