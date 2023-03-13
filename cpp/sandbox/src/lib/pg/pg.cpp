#ifndef PG
#define PG

#include "pg.h" // Pg
#include "connect.cpp"
#include "disconnect.cpp"
#include "exec.cpp"
#include "initialize.cpp" // initialize
#include <map>            // std::map

Pg::Pg(std::map<std::string, std::string> flags_ = {}) {
  this->flags = ::utils::map::merge(default_flags, flags_);
  initialize();
}

#endif
