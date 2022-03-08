#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include <map>
#include <string>

int main() {
  std::map<const char *, const char *> m = {{"jay", "z"}};
  const char *v = m["kanye"];

  if (v == nullptr) {
    puts("Empty value");
    return 0;
  }

  printf("Value: %s\n", v);
}
