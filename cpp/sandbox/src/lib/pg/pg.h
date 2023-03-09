#ifndef PG_H
#define PG_H

#include "lib/formatted.cpp" // Formatted
#include <libpq-fe.h>        // PGconn
#include <string>            // std::string
#include <vector>            // std::vector

class Pg {
public:
  Pg();

  PGconn *connect();
  void disconnect();
  std::vector<std::string> query(const std::string);

private:
  struct config_t {
    std::string host = "localhost";
    std::string name;
    std::string password;
    int port = 5432;
    std::string username;
  } config;

  Formatted::fmt_stream_t fmt = Formatted::stream();
  PGconn *conn;
  std::string db_uri;

  std::string build_connect_uri();

  void initialize();
  void load_config();
};

#endif
