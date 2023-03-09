#ifndef PG_disconnect
#define PG_disconnect

#include "pg.h"       // Pg, fmt
#include <iostream>   // std::cout, std::endl
#include <libpq-fe.h> // PQfinish
#include <stdio.h>    // printf

void Pg::disconnect() {
  PQfinish(this->conn);

  std::cout << fmt.bold << fmt.yellow;
  printf("👋 Successfully disconnected from %s", this->config.name.c_str());
  std::cout << fmt.reset << std::endl;
}

#endif
