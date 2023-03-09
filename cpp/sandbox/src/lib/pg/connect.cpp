#ifndef PG_connect
#define PG_connect

#include "pg.h"       // Pg, fmt
#include <iostream>   // std::cout, std::endl
#include <libpq-fe.h> // CONNECTION_OK, PGconn, PQconnectdb, PQstatus
#include <stdio.h>    // printf

PGconn *Pg::connect() {
  this->conn = PQconnectdb(this->db_uri.c_str());

  const int conn_status = PQstatus(this->conn);

  switch (conn_status) {
  case CONNECTION_OK: {
    std::cout << fmt.bold << fmt.yellow;
    printf("🚪 Successfully connected to %s", this->config.name.c_str());
    std::cout << fmt.reset << std::endl;

    break;
  }
  default: {
    std::cout << fmt.bold << fmt.red;
    printf("❌ Connection to %s failed. Status: %i", this->config.name.c_str(),
           conn_status);
    std::cout << fmt.reset << std::endl;
  }
  }

  return this->conn;
}

#endif
