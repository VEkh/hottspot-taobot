#ifndef CLI_H
#define CLI_H

#include "lib/formatted.cpp" // Formatted
#include <list>              // std::list
#include <map>               // std::map
#include <string>            // std::string

class Cli {
public:
  Cli(int c, char **v) : argc(c), argv(v){};

  void run();

protected:
  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::list<std::string> args;
  std::list<std::string> upcased_args;

  std::map<std::string, std::string> commands = {
      {"command", "description"},
  };

  std::map<std::string, std::string> flags;
  std::string cli_name = "Global";
  std::string command;

  void handle_unknown_command();

private:
  char **argv;
  int argc;

  void initialize();
  void print_usage();

  virtual void execute() { handle_unknown_command(); };
};

#endif
