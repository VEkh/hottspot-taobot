#if !defined TD_AMERITRADE_CLIENT__WRITE_RESPONSE_TO_FILE
#define TD_AMERITRADE_CLIENT__WRITE_RESPONSE_TO_FILE

#include "td_ameritrade_client.h" // TdAmeritradeClient
#include <fstream>                // std::ios, std::ofstream
#include <string>                 // std::string

void TdAmeritradeClient::write_response_to_file(std::string body,
                                                const char *file_path) {
  std::ofstream output_file(file_path, std::ios::out | std::ios::trunc);
  output_file << body;
  output_file.close();
}

#endif
