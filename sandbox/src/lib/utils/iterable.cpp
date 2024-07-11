#ifndef UTILS__ITERABLE
#define UTILS__ITERABLE

#include <map> // std::map

namespace utils {
namespace iterable {
template <template <typename> class IterableType, class ItemType>
bool are_equal(IterableType<ItemType> a, IterableType<ItemType> b) {
  if (a.size() != b.size()) {
    return false;
  }

  std::map<ItemType, bool> check;

  for (const ItemType item : b) {
    check[item] = true;
  }

  for (const ItemType item : a) {
    if (!check[item]) {
      return false;
    }
  }

  return true;
}

template <template <typename> class IterableType, class ItemType>
void print(IterableType<ItemType> collection) {
  for (const ItemType item : collection) {
    std::cout << item << std::endl;
  }
}

} // namespace iterable
} // namespace utils

#endif
