#if !defined TD_AMERITRADE_CLIENT__BUILD_ERROR_MESSAGE
#define TD_AMERITRADE_CLIENT__BUILD_ERROR_MESSAGE

#include "td_ameritrade_client.h" // TdAmeritradeClient, stream_format
#include <sstream>                  // std::ostringstream
#include <string>                   // std::string

std::string TdAmeritradeClient::build_error_message(std::string message) {
  std::ostringstream formatted_message;

  formatted_message << stream_format.bold << stream_format.red << message
                    << stream_format.reset;

  return formatted_message.str();
}

#endif
