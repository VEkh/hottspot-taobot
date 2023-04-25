#ifndef PG_H
#define PG_H

#include "lib/formatted.cpp" // Formatted
#include "lib/utils/map.cpp" // ::utils::map
#include <libpq-fe.h>        // PGconn
#include <map>               // std::map
#include <string>            // std::string
#include <vector>            // std::vector

class Pg {
public:
  Pg(std::map<std::string, std::string> f);

  struct query_result_t {
    std::string error_message = "";
    std::vector<std::string> fields = {};
    int fields_n = 0;
    int rows_n = 0;
    int status = 0;
    std::vector<std::string> tuples = {};
  };

  PGconn *conn = nullptr;
  std::map<std::string, std::string> flags;

  PGconn *connect();

  query_result_t exec(const std::string, const bool);

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
  std::map<std::string, std::string> default_flags = {
      {"env", "development"},
  };
  std::string db_uri;

  std::string build_connect_uri();

  void initialize();
  void load_config();
};

#endif
