#include <iostream>

#include <map>

std::map<const char *, const char *> ICONS = {
    {"BUY", "📈"},
    {"SELL_SHORT", "📉"},
};

int main() {
  bool *status = nullptr;
  bool s = true;
  status = &s;
  *status = false;

  if (status) {
    std::cout << *status << std::endl;
  }
}
