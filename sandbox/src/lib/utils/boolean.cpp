#ifndef UTILS__BOOLEAN
#define UTILS__BOOLEAN

#include "lib/utils/time.cpp" // ::utils::time_
#include <stdlib.h>           // rand, srand

namespace utils {
namespace boolean {
bool flip_coin() {
  srand(::utils::time_::epoch("nanoseconds"));
  const bool coin[] = {false, true};
  const int side_index = rand() % 2;

  return coin[side_index];
}
} // namespace boolean
} // namespace utils
#endif
