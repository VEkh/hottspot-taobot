#include "lib/utils/time.cpp" // utils::time_
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "Is EOD? " << utils::time_::is_end_of_day() << std::endl;
}
