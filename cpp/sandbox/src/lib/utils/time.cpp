#if !defined UTILS__TIME
#define UTILS__TIME

#include <chrono> // std::chrono, std::duration
#include <map>    // std::map

#include <ratio> // std::nano

namespace utils {
namespace time {

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
} // namespace time
} // namespace utils

#endif
