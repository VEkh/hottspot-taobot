#if !defined TD_AMERITRADE__CLIENT_write_response_to_file
#define TD_AMERITRADE__CLIENT_write_response_to_file

#include "client.h" // TdAmeritrade::Client
#include <fstream>  // std::ios, std::ofstream
#include <string>   // std::string

void TdAmeritrade::Client::write_response_to_file(std::string body,
                                                  const char *file_path) {
  std::ofstream output_file(file_path, std::ios::out | std::ios::trunc);
  output_file << body;
  output_file.close();
}

#endif
