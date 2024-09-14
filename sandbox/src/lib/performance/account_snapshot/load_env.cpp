#ifndef PERFORMANCE__ACCOUNT_SNAPSHOT_load_env
#define PERFORMANCE__ACCOUNT_SNAPSHOT_load_env

#include "account_snapshot.h" // Performance::AccountSnapshot, fmt
#include "deps.cpp"           // json
#include "lib/utils/io.cpp"   // ::utils::io
#include <iostream>           // std::cout, std::endl
#include <stdio.h>            // puts

void Performance::AccountSnapshot::load_env() {
  const json config_json =
      ::utils::io::load_config(this->config.api_name, this->config.api_key);

  const json api_key_json = config_json[this->config.api_key];

  this->config.api_key_id = api_key_json["id"];

  std::cout << fmt.bold << fmt.cyan;
  std::cout << "\nEnvironment: " << fmt.yellow << this->config.api_key.c_str();
  std::cout << fmt.cyan << std::endl << std::endl;
  puts(api_key_json.dump(2).c_str());
  std::cout << fmt.reset;
}

#endif
