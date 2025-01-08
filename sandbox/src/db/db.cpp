#include "cli/cli.cpp"

int main(int argc, char *argv[]) {
  DB::Cli cli(argc, argv);

  cli.run();

  exit(0);
}
