#include "utils/formatted.cpp" // Formatted::stream, Formatted::fmt_stream_t
#include <iostream>            // std::cout

int main() {
  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::cout << fmt.green << "SUCCESS" << std::endl;
}
