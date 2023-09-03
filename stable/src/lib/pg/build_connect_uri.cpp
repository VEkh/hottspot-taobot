#ifndef PG_build_connect_uri
#define PG_build_connect_uri

#include "pg.h"    // Pg
#include <sstream> // std::stringstream
#include <string>  // std::string

std::string Pg::build_connect_uri() {
  std::stringstream out;

  out << "postgres://" << this->config.username << ":" << this->config.password
      << "@" << this->config.host << ":" << this->config.port << "/"
      << this->config.name;

  return out.str();
}

#endif
