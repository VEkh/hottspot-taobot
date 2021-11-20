#ifndef ETRADE__TAO_BOT_flip_coin
#define ETRADE__TAO_BOT_flip_coin

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // ETrade::TaoBot
#include <stdlib.h>           // rand, srand

bool ETrade::TaoBot::flip_coin() {
  srand(::utils::time_::epoch("nanoseconds"));
  const bool coin[] = {false, true};
  const int side_index = rand() % 2;

  return coin[side_index];
}

#endif
