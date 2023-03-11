#ifndef PG_exec
#define PG_exec

/*
 * ExecStatusType
 * PGresult
 * PQclear
 * PQcmdStatus
 * PQexec
 * PQfname
 * PQgetvalue
 * PQnfields
 * PQntuples
 * PQresStatus
 * PQresultErrorMessage
 * PQresultStatus
 */
#include <libpq-fe.h>

#include "lib/utils/vector.cpp" // ::utils::vector
#include "pg.h"                 // Pg, fmt, query_result_t
#include <iostream>             // std::cout, std::endl, std::flush
#include <string>               // std::string
#include <vector>               // std::vector

Pg::query_result_t Pg::exec(const std::string q) {
  std::cout << fmt.bold << fmt.cyan;
  printf("%s\n", q.c_str());
  std::cout << fmt.reset << std::flush;

  PGresult *res = PQexec(this->conn, q.c_str());
  query_result_t result;

  result.fields_n = PQnfields(res);
  result.rows_n = PQntuples(res);
  result.status = PQresultStatus(res);

  const char *result_status_string = PQresStatus((ExecStatusType)result.status);

  std::cout << fmt.bold << fmt.cyan;
  printf("%s\n", result_status_string);
  std::cout << fmt.reset << std::flush;

  switch (result.status) {
  case ExecStatusType::PGRES_COMMAND_OK:
  case ExecStatusType::PGRES_TUPLES_OK: {
    const char *cmd_status = PQcmdStatus(res);

    std::cout << fmt.bold << fmt.magenta;
    printf("%s\n", cmd_status);

    for (int col = 0; col < result.fields_n; col++) {
      result.fields.push_back(PQfname(res, col));
    }

    if (result.rows_n) {
      printf("%s\n", ::utils::vector::join(result.fields, ",").c_str());
    }

    for (int row = 0; row < result.rows_n; row++) {
      int col = 0;

      std::string tuple = PQgetvalue(res, row, col);

      for (col = 1; col < result.fields_n; col++) {
        tuple += std::string(",") + std::string(PQgetvalue(res, row, col));
      }

      printf("%s\n", tuple.c_str());

      result.tuples.push_back(tuple);
    }

    std::cout << fmt.reset << std::flush;

    break;
  }
  default: {
    const char *error_message = PQresultErrorMessage(res);
    result.error_message = error_message;

    std::cout << fmt.bold << fmt.red;
    printf("Error Message: %s", error_message);
    std::cout << fmt.reset << std::flush;
  }
  }

  PQclear(res);

  return result;
}

#endif
