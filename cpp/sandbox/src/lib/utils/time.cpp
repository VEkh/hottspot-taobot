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

bool is_early_day() {
  const char *original_tz = getenv("TZ");
  time_t local_now;

  setenv("TZ", "America/New_York", 1);
  time(&local_now);
  std::tm local_time = *std::localtime(&local_now);

  const bool out = local_time.tm_hour < 11;

  if (original_tz) {
    setenv("TZ", original_tz, 1);
  } else {
    unsetenv("TZ");
  }

  return out;
}

bool is_end_of_day() {
  const char *original_tz = getenv("TZ");
  time_t local_now;

  setenv("TZ", "America/New_York", 1);
  time(&local_now);
  std::tm local_time = *std::localtime(&local_now);

  const bool out = local_time.tm_hour == 15 && local_time.tm_min == 59;

  if (original_tz) {
    setenv("TZ", original_tz, 1);
  } else {
    unsetenv("TZ");
  }

  return out;
}

bool is_market_open() {
  const char *original_tz = getenv("TZ");
  time_t local_now;

  setenv("TZ", "America/New_York", 1);
  time(&local_now);
  std::tm local_time = *std::localtime(&local_now);

  bool valid_hour = local_time.tm_hour >= 9 && local_time.tm_hour < 16;
  bool valid_min = local_time.tm_hour == 9 ? local_time.tm_min >= 30 : true;

  const bool out = valid_hour && valid_min;

  if (original_tz) {
    setenv("TZ", original_tz, 1);
  } else {
    unsetenv("TZ");
  }

  return out;
}
} // namespace time_
} // namespace utils

#endif
