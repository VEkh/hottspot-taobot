#ifndef PG_query
#define PG_query

/*
 * PGresult
 * PQclear
 * PQexec
 * PQgetvalue
 * PQnfields
 * PQntuples
 */
#include <libpq-fe.h>

#include "pg.h"     // Pg, fmt
#include <iostream> // std::cout, std::endl, std::flush
#include <string>   // std::string
#include <vector>   // std::vector

std::vector<std::string> Pg::query(const std::string q) {
  PGresult *res = PQexec(this->conn, q.c_str());

  const int cols = PQnfields(res);
  const int rows = PQntuples(res);
  std::vector<std::string> result;

  std::cout << fmt.bold << fmt.cyan;
  printf("%s\n", q.c_str());
  std::cout << fmt.reset << std::flush;

  for (int row = 0; row < rows; row++) {
    int col = 0;

    std::string tuple = PQgetvalue(res, row, col);

    for (col = 1; col < cols; col++) {
      tuple += std::string(",") + std::string(PQgetvalue(res, row, col));
    }

    std::cout << fmt.bold << fmt.magenta;
    printf("%s\n", tuple.c_str());
    std::cout << fmt.reset << std::flush;

    result.push_back(tuple);
  }

  PQclear(res);

  return result;
}

#endif
