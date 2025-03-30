#ifndef UTILS__STATS
#define UTILS__STATS

#include <list>   // std::list
#include <math.h> // pow, sqrt

namespace utils {
namespace stats {
template <typename Numeric> double mean(const std::list<Numeric> data) {
  int count = 0;
  double sum = 0;

  for (const Numeric datum : data) {
    sum += datum;
    count++;
  }

  return sum / count;
}

template <typename Numeric> double median(const std::list<Numeric> data) {
  int i = 0;
  const int count = data.size();
  const int median_i = count / 2;

  for (const Numeric datum : data) {
    if (i == median_i) {
      return datum;
    }

    i++;
  }

  return 0.0;
}

template <typename Numeric> double std(const std::list<Numeric> data) {
  const double avg = mean(data);

  double sum = 0;
  int count = data.size();

  for (const Numeric datum : data) {
    sum += pow((datum - avg), 2);
  }

  return sqrt(sum / count);
}
} // namespace stats
} // namespace utils

#endif
