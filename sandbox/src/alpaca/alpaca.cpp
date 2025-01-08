#include "cli/cli.cpp" // Alpaca::Cli

int main(int argc, char *argv[]) {
  Alpaca::Cli cli(argc, argv);

  cli.run();
}
