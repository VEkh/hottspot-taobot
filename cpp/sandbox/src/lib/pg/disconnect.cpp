#ifndef PG_disconnect
#define PG_disconnect

#include "pg.h"       // Pg, fmt
#include <iostream>   // std::cout, std::endl
#include <libpq-fe.h> // PQfinish
#include <stdio.h>    // printf

void Pg::disconnect() {
  if (this->conn == nullptr) {
    const std::string error_message = Formatted::error_message(
        "Pg::initialize must be run before a connection can be terminated.");

    throw std::invalid_argument(error_message);
  }

  PQfinish(this->conn);

  std::cout << fmt.bold << fmt.yellow;
  std::cout << "👋 Successfully disconnected from ";
  std::cout << fmt.green << this->config.name;
  std::cout << fmt.reset << std::endl;
}

#endif
