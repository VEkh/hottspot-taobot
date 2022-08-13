#ifndef UTILS__TIME
#define UTILS__TIME

#include <chrono>   // std::chrono, std::duration
#include <ctime>    // std::localtime, std::mktime, struct std::tm
#include <iomanip>  // std::setw
#include <iostream> // std::fixed
#include <map>      // std::map
#include <ratio>    // std::nano
#include <sstream>  // std::ostringstream
#include <stdlib.h> // getenv, setenv, unsetenv
#include <string>   // std::string
#include <time.h>   // localtime, strftime, struct tm, time, time_t
#include <vector>   // std::vector

namespace utils {
namespace time_ {
unsigned long epoch(const std::string duration = "seconds") {
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

  return 0;
}

template <typename ReturnType, typename Predicate>
ReturnType in_time_zone(const char *time_zone, Predicate fn) {
  return in_time_zone<ReturnType>(time_zone, &fn);
}

template <typename ReturnType, typename Predicate>
ReturnType in_time_zone(const char *time_zone, Predicate *fn) {
  const char *original_tz = getenv("TZ");
  setenv("TZ", time_zone, 1);

  const ReturnType out = (*fn)();

  if (original_tz) {
    setenv("TZ", original_tz, 1);
  } else {
    unsetenv("TZ");
  }

  return out;
}

int day_of_week() {
  return in_time_zone<int>("America/New_York", []() -> int {
    time_t local_now;
    time(&local_now);
    std::tm local_time = *std::localtime(&local_now);

    return local_time.tm_wday;
  });
}

std::string date_string(const long int timestamp_seconds,
                        const char *format = "%F",
                        const char *timezone = "America/New_York") {
  return in_time_zone<std::string>(timezone, [&]() -> std::string {
    struct tm *timeinfo;
    const int buffer_size = 100;

    char buffer[buffer_size];

    timeinfo = localtime(&timestamp_seconds);

    strftime(buffer, buffer_size, format, timeinfo);

    return buffer;
  });
}

bool is_at_least(const std::vector<int> time_parts) {
  return in_time_zone<bool>("America/New_York", [&]() -> bool {
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
  return in_time_zone<bool>("America/New_York", [&]() -> bool {
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

std::tm parse_timestamp(std::string in, const char *format) {
  std::tm datetime = {};
  std::istringstream date_string(in);

  date_string >> std::get_time(&datetime, format);

  std::mktime(&datetime);

  return datetime;
}

std::string timestamp_to_clock(time_t timestamp,
                               const char *time_zone = "America/New_York") {
  return in_time_zone<std::string>(time_zone, [&]() -> std::string {
    tm quote_time = *localtime(&timestamp);
    std::ostringstream out;

    out << std::setfill('0') << std::setw(2) << quote_time.tm_hour << ":"
        << std::setfill('0') << std::setw(2) << quote_time.tm_min;

    return out.str();
  });
};

} // namespace time_
} // namespace utils

#endif
