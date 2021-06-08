#ifndef UTILS__TIME
#define UTILS__TIME

#include <chrono>   // std::chrono, std::duration
#include <ctime>    // time, time_t, tm
#include <map>      // std::map
#include <ratio>    // std::nano
#include <stdlib.h> // setnev, unsetenv

namespace utils {
namespace time_ {
unsigned long epoch(const char *duration = "seconds") {
  std::chrono::duration<long, std::nano> now_in_nano =
      std::chrono::system_clock::now().time_since_epoch();

  if (duration == "seconds") {
    return std::chrono::duration_cast<std::chrono::seconds>(now_in_nano)
        .count();
  }

  if (duration == "milliseconds") {
    return std::chrono::duration_cast<std::chrono::milliseconds>(now_in_nano)
        .count();
  }

  if (duration == "nanoseconds") {
    return now_in_nano.count();
  }
}

bool is_end_of_day() {
  const char *original_tz = getenv("TZ");
  time_t local_now;

  setenv("TZ", "America/New_York", 1);
  time(&local_now);
  std::tm local_time = *std::localtime(&local_now);

  const bool is_eod = local_time.tm_hour == 15 && local_time.tm_min == 57;

  if (original_tz) {
    setenv("TZ", original_tz, 1);
  } else {
    unsetenv("TZ");
  }

  return is_eod;
}
} // namespace time_
} // namespace utils

#endif
