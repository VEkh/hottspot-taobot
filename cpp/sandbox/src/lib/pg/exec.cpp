#ifndef PG_exec
#define PG_exec

/*
 * ExecStatusType
 * PGresult
 * PQclear
 * PQcmdStatus
 * PQexec
 * PQgetvalue
 * PQnfields
 * PQntuples
 * PQresStatus
 * PQresultErrorMessage
 * PQresultStatus
 */
#include <libpq-fe.h>

#include "pg.h"     // Pg, fmt
#include <iostream> // std::cout, std::endl, std::flush
#include <string>   // std::string
#include <vector>   // std::vector

std::vector<std::string> Pg::exec(const std::string q) {
  PGresult *res = PQexec(this->conn, q.c_str());

  const int cols = PQnfields(res);
  const int rows = PQntuples(res);
  std::vector<std::string> result;

  std::cout << fmt.bold << fmt.cyan;
  printf("%s\n", q.c_str());
  std::cout << fmt.reset << std::flush;

  ExecStatusType result_status = PQresultStatus(res);
  const char *result_status_string = PQresStatus(result_status);

  std::cout << fmt.bold << fmt.cyan;
  printf("%s\n", result_status_string);
  std::cout << fmt.reset << std::flush;

  switch (result_status) {
  case ExecStatusType::PGRES_COMMAND_OK:
  case ExecStatusType::PGRES_TUPLES_OK: {
    const char *cmd_status = PQcmdStatus(res);

    std::cout << fmt.bold << fmt.magenta;
    printf("%s\n", cmd_status);

    for (int row = 0; row < rows; row++) {
      int col = 0;

      std::string tuple = PQgetvalue(res, row, col);

      for (col = 1; col < cols; col++) {
        tuple += std::string(",") + std::string(PQgetvalue(res, row, col));
      }

      printf("%s\n", tuple.c_str());

      result.push_back(tuple);
    }

    std::cout << fmt.reset << std::flush;

    break;
  }
  default: {
    const char *error_message = PQresultErrorMessage(res);

    std::cout << fmt.bold << fmt.red;
    printf("Error Message: %s\n", error_message);
    std::cout << fmt.reset << std::flush;
  }
  }

  PQclear(res);

  return result;
}

#endif
