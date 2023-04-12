#ifndef UTILS__TIME
#define UTILS__TIME

#include <chrono>   // std::chrono, std::duration
#include <iomanip>  // std::setw
#include <iostream> // std::fixed
#include <map>      // std::map
#include <ratio>    // std::nano
#include <regex>    // std::cmatch, std::regex, std::regex_search
#include <sstream>  // std::ostringstream
#include <stdlib.h> // getenv, setenv, unsetenv
#include <string>   // std::string
#include <time.h>   // localtime, mktime, strftime, struct tm, time, time_t
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

int day_of_week(const long int epoch) {
  return in_time_zone<int>("America/New_York", [&]() -> int {
    tm local_time = *localtime(&epoch);

    return local_time.tm_wday;
  });
}

int day_of_week() {
  const long int now = time(nullptr);
  return day_of_week(now);
}

bool is_at_least(const long int epoch, const std::vector<int> time_parts,
                 const char *time_zone = "America/New_York") {
  if (time_parts.empty()) {
    return false;
  }

  return in_time_zone<bool>(time_zone, [&]() -> bool {
    tm local_time = *localtime(&epoch);

    const int hours = time_parts[0];
    const int minutes = time_parts.size() > 1 ? time_parts[1] : 0;

    bool out = local_time.tm_hour >= hours;

    if (out && local_time.tm_hour == hours && minutes) {
      out = local_time.tm_min >= minutes;
    }

    return out;
  });
}

bool is_at_least(const std::vector<int> time_parts,
                 const char *time_zone = "America/New_York") {
  const long int now = time(nullptr);
  return is_at_least(now, time_parts, time_zone);
}

bool is_before(const long int epoch, const std::vector<int> time_parts,
               const char *time_zone = "America/New_York") {
  if (time_parts.empty()) {
    return false;
  }

  return in_time_zone<bool>(time_zone, [&]() -> bool {
    tm local_time = *localtime(&epoch);

    const int hours = time_parts[0];
    const int minutes = time_parts.size() > 1 ? time_parts[1] : 0;

    bool out = local_time.tm_hour < hours;

    if (!out && local_time.tm_hour == hours && minutes) {
      out = local_time.tm_min < minutes;
    }

    return out;
  });
}

bool is_before(const std::vector<int> time_parts,
               const char *time_zone = "America/New_York") {
  const long int now = time(nullptr);
  return is_before(now, time_parts, time_zone);
}

tm parse_timestamp(std::string in, const char *format) {
  tm datetime = {};
  std::istringstream date_string_(in);

  date_string_ >> std::get_time(&datetime, format);

  mktime(&datetime);

  return datetime;
}

double beginning_of_day_to_epoch(const long int now) {
  std::string now_string = date_string(now, "%F", "America/Chicago");
  tm date_start = parse_timestamp(now_string, "%Y-%m-%d");
  const double day_start_epoch = mktime(&date_start);

  return day_start_epoch;
}

double quote_timestamp_to_epoch_double(const char *timestamp) {
  tm parsed = parse_timestamp(timestamp, "%Y-%m-%dT%H:%M:%SZ");
  const int epoch = mktime(&parsed);
  double seconds_decimal = 0;

  std::cmatch match;

  if (std::regex_search(timestamp, match, std::regex("\\d{2}(\\.\\d+)Z$")) &&
      match.size() > 1) {
    seconds_decimal = std::stod(match[1]);
  }

  return epoch + seconds_decimal;
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
