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
    std::cout << "🚪 Successfully connected to ";
    std::cout << fmt.green << this->config.name;
    std::cout << fmt.reset << std::endl;

    break;
  }
  default: {
    std::cout << fmt.bold << fmt.red;
    printf("❌ Connection to %s failed. Status: %i", this->config.name.c_str(),
           conn_status);
    std::cout << fmt.reset << std::endl;
    exit(1);
  }
  }

  return this->conn;
}

#endif
