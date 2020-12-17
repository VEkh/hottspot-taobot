#if !defined UTILS__IO
#define UTILS__IO

#include <fstream> // std::ios, std::ofstream
#include <string>  // std::string

namespace utils {
namespace io {
void write_to_file(std::string body, const char *file_path) {
  std::ofstream output_file(file_path, std::ios::out | std::ios::trunc);
  output_file << body;
  output_file.close();
}
} // namespace io
} // namespace utils

#endif
