#ifndef PG_build_connect_uri
#define PG_build_connect_uri

#include "pg.h"     // Pg
#include <stdio.h>  // snprintf
#include <string.h> // strlen
#include <string>   // std::string, std::to_string

std::string Pg::build_connect_uri() {
  const char *format = "postgres://%s:%s@%s:%i/%s";

  const size_t size = strlen(format) + this->config.username.size() +
                      this->config.password.size() + this->config.host.size() +
                      std::to_string(this->config.port).size() +
                      this->config.name.size();

  char uri[size];

  snprintf(uri, size, format, this->config.username.c_str(),
           this->config.password.c_str(), this->config.host.c_str(),
           this->config.port, this->config.name.c_str());

  return uri;
}

#endif
