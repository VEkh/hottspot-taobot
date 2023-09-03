#ifndef PG__await_notification
#define PG__await_notification

#include "exec.cpp" // exec
#include "pg.h"     // Pg, await_notification_args_t
#include <iostream> // std::cout, std::endl
#include <libpq-fe.h> // PGnotify, PQconsumeInput, PQescapeIdentifier, PQfreemem, PQsocket
#include <stdio.h>      // printf, puts
#include <string.h>     // snprintf, strlen
#include <string>       // std::string
#include <sys/select.h> // FD_SET, FD_ZERO, fd_set, select, timeval

std::string Pg::await_notification(const await_notification_args_t args) {
  const bool debug = args.debug;
  const int timeout_microseconds = args.timeout_microseconds;
  const int timeout_seconds = args.timeout_seconds;
  const std::string channel = args.channel;

  char *sanitized_channel =
      PQescapeIdentifier(this->conn, channel.c_str(), channel.size());

  const char *listen_query_format = "listen %s";

  const size_t listen_query_l =
      strlen(listen_query_format) + strlen(sanitized_channel);

  char listen_query[listen_query_l];

  snprintf(listen_query, listen_query_l, listen_query_format,
           sanitized_channel);

  PQfreemem(sanitized_channel);

  const std::string unlisten_query = std::string("un") + listen_query;

  PGnotify *notify = nullptr;
  fd_set input_mask;
  timeval *timeout_ptr = nullptr;

  int socket = PQsocket(this->conn);

  if (socket < 0) {
    std::cout << fmt.bold << fmt.red;
    puts("Failed to get valid socket. Reconnecting.");
    std::cout << fmt.reset;

    return "";
  }

  exec(listen_query, debug);

  FD_ZERO(&input_mask);
  FD_SET(socket, &input_mask);

  if (timeout_microseconds || timeout_seconds) {
    timeval timeout = {
        .tv_sec = timeout_seconds,
        .tv_usec = timeout_microseconds,
    };

    timeout_ptr = &timeout;
  }

  const int is_notification_ready =
      select(socket + 1, &input_mask, nullptr, nullptr, timeout_ptr);

  if (is_notification_ready) {
    std::string out;

    PQconsumeInput(this->conn);

    notify = PQnotifies(this->conn);

    if (notify != nullptr) {
      PQconsumeInput(this->conn);

      out = notify->extra;
    } else {
      std::cout << fmt.bold << fmt.yellow;
      puts("No published notifications");
      std::cout << fmt.reset;
    }

    PQfreemem(notify);

    exec(unlisten_query, debug);
    return out;
  } else if (is_notification_ready == -1) {
    std::cout << fmt.bold << fmt.red;
    puts("Connection was lost. Reconnecting");
    std::cout << fmt.reset;

    return "";
  } else {
    std::cout << fmt.bold << fmt.yellow;
    puts("Socket not ready.");
    std::cout << fmt.reset;
  }

  exec(unlisten_query, debug);

  return "";
}

#endif
