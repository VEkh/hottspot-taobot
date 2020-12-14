#if !defined ETRADE__CLIENT_write_response_to_file
#define ETRADE__CLIENT_write_response_to_file

#include "client.h" // ETrade::Client
#include <fstream>  // std::ios, std::ofstream
#include <string>   // std::string

void ETrade::Client::write_response_to_file(std::string body,
                                            const char *file_path) {
  std::ofstream output_file(file_path, std::ios::out | std::ios::trunc);
  output_file << body;
  output_file.close();
}

#endif
