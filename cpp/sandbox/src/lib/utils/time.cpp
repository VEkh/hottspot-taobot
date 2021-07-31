#ifndef UTILS__TIME
#define UTILS__TIME

#include <chrono>   // std::chrono, std::duration
#include <ctime>    // time, time_t, tm
#include <map>      // std::map
#include <ratio>    // std::nano
#include <stdlib.h> // getenv, setenv, unsetenv
#include <vector>   // std::vector

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

template <typename Predicate>
bool in_time_zone(const char *time_zone, Predicate fn) {
  return in_time_zone(time_zone, &fn);
}

template <typename Predicate>
bool in_time_zone(const char *time_zone, Predicate *fn) {
  const char *original_tz = getenv("TZ");
  setenv("TZ", time_zone, 1);

  const bool out = (*fn)();

  if (original_tz) {
    setenv("TZ", original_tz, 1);
  } else {
    unsetenv("TZ");
  }

  return out;
}

bool is_at_least(const std::vector<int> time_parts) {
  return in_time_zone("America/New_York", [&]() -> bool {
    time_t local_now;
    time(&local_now);
    std::tm local_time = *std::localtime(&local_now);

    if (time_parts.empty()) {
      return false;
    }

    const int hours = time_parts[0];
    const int minutes = time_parts.size() > 1 ? time_parts[1] : 0;

    bool out = local_time.tm_hour >= hours;

    if (out && local_time.tm_hour == hours && minutes) {
      out = local_time.tm_min >= minutes;
    }

    return out;
  });
}

bool is_before(const std::vector<int> time_parts) {
  return in_time_zone("America/New_York", [&]() -> bool {
    if (time_parts.empty()) {
      return false;
    }

    time_t local_now;

    time(&local_now);
    std::tm local_time = *std::localtime(&local_now);

    const int hours = time_parts[0];
    const int minutes = time_parts.size() > 1 ? time_parts[1] : 0;

    bool out = local_time.tm_hour < hours;

    if (!out && local_time.tm_hour == hours && minutes) {
      out = local_time.tm_min < minutes;
    }

    return out;
  });
}

bool is_early_day() { return is_before({11, 0}); }
bool is_end_of_day() { return is_at_least({15, 59}) && is_before({16, 0}); }
bool is_market_open() { return is_at_least({9, 30}) && is_before({16, 0}); }

} // namespace time_
} // namespace utils

#endif
