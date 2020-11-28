#if !defined TD_AMERITRADE__STRADDLE_H
#define TD_AMERITRADE__STRADDLE_H

namespace TdAmeritrade {
class Straddle {
public:
  Straddle(char *, int);

  void run();

private:
  int quantity;
  char *symbol;
};
} // namespace TdAmeritrade

#endif
