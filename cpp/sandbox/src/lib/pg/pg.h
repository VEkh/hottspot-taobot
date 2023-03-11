#ifndef PG_H
#define PG_H

#include "lib/formatted.cpp" // Formatted
#include <libpq-fe.h>        // PGconn
#include <string>            // std::string
#include <vector>            // std::vector

class Pg {
public:
  Pg();

  struct query_result_t {
    std::string error_message = "";
    std::vector<std::string> fields = {};
    int fields_n = 0;
    int rows_n = 0;
    int status = 0;
    std::vector<std::string> tuples = {};
  };

  PGconn *conn;

  PGconn *connect();

  query_result_t exec(const std::string);

  void disconnect();

private:
  struct config_t {
    std::string host = "localhost";
    std::string name;
    std::string password;
    int port = 5432;
    std::string username;
  } config;

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::string db_uri;

  std::string build_connect_uri();

  void initialize();
  void load_config();
};

#endif
