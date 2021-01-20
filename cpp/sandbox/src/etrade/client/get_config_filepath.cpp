#if !defined ETRADE__CLIENT_get_config_filepath
#define ETRADE__CLIENT_get_config_filepath

#include "client.h" // CONFIG_PATH, ETrade::Client, client_config
#include <libgen.h> // dirname
#include <limits.h> // PATH_MAX
#include <stdlib.h> // realpath
#include <string>   // std::string
#include <unistd.h> // readlink

std::string ETrade::Client::get_config_filepath(const char *key) {
  char execuable_path[PATH_MAX];
  char resolved_path[PATH_MAX];

  if (!client_config.paths[key].empty()) {
    return client_config.paths[key];
  }

  std::map<const char *, std::string> paths = {
      {"config", "config/etrade/credentials.json"},
      {"tokens", "config/etrade/tokens.json"},
  };

  readlink("/proc/self/exe", execuable_path, PATH_MAX);

  std::string directory = std::string(dirname(execuable_path));
  std::string unresolved_path = directory + "/../" + paths[key];

  realpath(unresolved_path.c_str(), resolved_path);

  client_config.paths[key] = resolved_path;

  return resolved_path;
}

#endif
