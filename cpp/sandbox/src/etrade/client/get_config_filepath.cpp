#ifndef ETRADE__CLIENT_get_config_filepath
#define ETRADE__CLIENT_get_config_filepath

#include "client.h" // ETrade::Client, config
#include <string>   // std::string

std::string ETrade::Client::get_config_filepath(const char *key) {
  if (!config.paths[key].empty()) {
    return config.paths[key];
  }

  std::map<const char *, std::string> paths = {
      {"config", "/config/etrade/credentials.json"},
      {"tokens", "/config/etrade/tokens.json"},
  };

  std::string filepath = std::string(APP_DIR) + paths[key];

  config.paths[key] = filepath;

  return filepath;
}

#endif
