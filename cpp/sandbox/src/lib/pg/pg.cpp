#ifndef PG
#define PG

#include "pg.h" // Pg
#include "connect.cpp"
#include "disconnect.cpp"
#include "initialize.cpp" // initialize
#include "query.cpp"

Pg::Pg() { initialize(); }

#endif
