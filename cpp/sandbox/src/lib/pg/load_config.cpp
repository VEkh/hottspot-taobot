#ifndef PG_load_config
#define PG_load_config

#include "deps.cpp" // json
#include "pg.h"     // Pg, fmt
#include <fstream>  // std::ifstream, std::ios
#include <iostream> // std::endl
#include <sstream>  // std::stringstream
#include <string>   // std::string

void Pg::load_config() {
  const std::string filepath =
      std::string(APP_DIR) + "/config/db/credentials.json";

  std::ifstream config_file(filepath.c_str(), std::ios::in);

  if (!config_file.good()) {
    std::stringstream stream;

    stream << fmt.bold << fmt.red;
    stream << "❗ Database config file does not exist." << std::endl;
    stream << fmt.yellow;
    stream << "Create it using " << filepath << ".example";
    stream << fmt.reset;

    throw std::invalid_argument(stream.str());
  }

  json config_json;
  config_file >> config_json;
  config_file.close();

  const std::string env = this->flags["env"];

  if (!config_json.contains(env)) {
    std::stringstream stream;

    stream << fmt.bold << fmt.red;
    stream << "❗ Database environment ";
    stream << fmt.yellow << env << fmt.red;
    stream << " is not specified in " << filepath << ".";
    stream << fmt.reset;

    throw std::invalid_argument(stream.str());
  }

  config_json = config_json[env];

  this->config.name = config_json["name"];
  this->config.password = config_json["password"];
  this->config.username = config_json["username"];

  if (config_json.contains("host")) {
    this->config.host = config_json["host"];
  }

  if (config_json.contains("port")) {
    this->config.port = config_json["port"];
  }
}

#endif
