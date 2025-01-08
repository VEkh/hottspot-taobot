#include "cli/cli.cpp" // Oanda::Cli

int main(int argc, char *argv[]) {
  Oanda::Cli cli(argc, argv);

  cli.run();
}
