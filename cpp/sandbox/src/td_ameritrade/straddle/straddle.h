#if !defined TD_AMERITRADE__STRADDLE_H
#define TD_AMERITRADE__STRADDLE_H

#include "lib/formatted.cpp"

namespace TdAmeritrade {
class Straddle {
public:
  Straddle(char *, int);

  void run();

private:
  int quantity;
  Formatted::fmt_stream_t stream_format = Formatted::stream();
  char *symbol;
};
} // namespace TdAmeritrade

#endif
