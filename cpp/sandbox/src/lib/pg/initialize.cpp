#ifndef PG_initialize
#define PG_initialize

#include "build_connect_uri.cpp" // build_connect_uri
#include "load_config.cpp"       // load_config
#include "pg.h"                  // Pg

void Pg::initialize() {
  load_config();
  this->db_uri = build_connect_uri();
}

#endif
