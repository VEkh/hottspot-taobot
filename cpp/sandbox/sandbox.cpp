#include <iostream>

struct t {
  int id = 0;
};

int main() {
  t type = {.id = 4};
  t *type_p = nullptr;

  *type_p = type;

  std::cout << type_p->id << std::endl;
}
