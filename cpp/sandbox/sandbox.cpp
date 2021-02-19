#include <cstring>
#include <iostream>

int main() {
  const char chars[] = {'c', 'h', 'a', 'r'};
  int l = sizeof(chars) / sizeof(*chars);

  char *a = nullptr;

  std::cout << (strcmp(nullptr, "BUY")) << std::endl;

  // std::cout << (5.0 / 14) << std::endl;
  // std::cout << (((821.0 - 792.44) / 816.12) * 0.06) << std::endl;
}
