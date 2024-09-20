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
                        const char *time_zone = "America/New_York") {
  return in_time_zone<std::string>(time_zone, [&]() -> std::string {
    struct tm *timeinfo;
    const int buffer_size = 100;

    char buffer[buffer_size];

    timeinfo = localtime(&timestamp_seconds);

    strftime(buffer, buffer_size, format, timeinfo);

    return buffer;
  });
}

int day_of_week(const long int epoch) {
  return in_time_zone<int>("America/Chicago", [&]() -> int {
    tm local_time = *localtime(&epoch);

    return local_time.tm_wday;
  });
}

int day_of_week() {
  const long int now = time(nullptr);
  return day_of_week(now);
}

tm epoch_to_tm(const long int epoch,
               const char *time_zone = "America/New_York") {
  return in_time_zone<tm>(time_zone,
                          [&]() -> tm { return *localtime(&epoch); });
}

bool is_at_least(const long int epoch, const tm time_parts,
                 const char *time_zone = "America/New_York") {
  return in_time_zone<bool>(time_zone, [&]() -> bool {
    tm ref_time = *localtime(&epoch);
    tm comparison_time = ref_time;

    comparison_time.tm_hour = time_parts.tm_hour;
    comparison_time.tm_min = time_parts.tm_min;
    comparison_time.tm_sec = time_parts.tm_sec;

    const long int comparison_time_epoch = mktime(&comparison_time);
    const long int ref_time_epoch = mktime(&ref_time);

    return ref_time_epoch >= comparison_time_epoch;
  });
}

bool is_at_least(const tm time_parts,
                 const char *time_zone = "America/New_York") {
  const long int now = time(nullptr);
  return is_at_least(now, time_parts, time_zone);
}

bool is_before(const long int epoch, const tm time_parts,
               const char *time_zone = "America/New_York") {
  return in_time_zone<bool>(time_zone, [&]() -> bool {
    tm ref_time = *localtime(&epoch);
    tm comparison_time = ref_time;

    comparison_time.tm_hour = time_parts.tm_hour;
    comparison_time.tm_min = time_parts.tm_min;
    comparison_time.tm_sec = time_parts.tm_sec;

    const long int comparison_time_epoch = mktime(&comparison_time);
    const long int ref_time_epoch = mktime(&ref_time);

    return ref_time_epoch < comparison_time_epoch;
  });
}

bool is_before(const tm time_parts,
               const char *time_zone = "America/New_York") {
  const long int now = time(nullptr);
  return is_before(now, time_parts, time_zone);
}

tm parse_timestamp(std::string in, const char *format) {
  tm datetime = {};
  std::istringstream date_string_(in);

  date_string_ >> std::get_time(&datetime, format);

  return datetime;
}

double beginning_of_day_to_epoch(const long int now) {
  std::string now_string = date_string(now, "%F", "America/Chicago");
  tm date_start = parse_timestamp(now_string, "%Y-%m-%d");
  const double day_start_epoch = mktime(&date_start);

  return day_start_epoch;
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

double tm_to_epoch(tm in, const char *time_zone = "America/New_York") {
  return in_time_zone<double>(time_zone,
                              [&]() -> double { return mktime(&in); });
}

} // namespace time_
} // namespace utils

#endif
