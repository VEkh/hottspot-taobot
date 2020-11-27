#if !defined TD_AMERITRADE__CLIENT_build_error_message
#define TD_AMERITRADE__CLIENT_build_error_message

#include "client.h" // TdAmeritrade::Client, stream_format
#include <sstream>  // std::ostringstream
#include <string>   // std::string

std::string TdAmeritrade::Client::build_error_message(std::string message) {
  std::ostringstream formatted_message;

  formatted_message << stream_format.bold << stream_format.red << message
                    << stream_format.reset;

  return formatted_message.str();
}

#endif
