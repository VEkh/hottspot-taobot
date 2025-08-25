#ifndef OANDA__CLIENT_load_env
#define OANDA__CLIENT_load_env

#include "client.h"         // Oanda::Client
#include "deps.cpp"         // json
#include "lib/utils/io.cpp" // ::utils::io

json Oanda::Client::load_env() {
  return ::utils::io::load_config("oanda", this->flags["api-key"]);
}

#endif
