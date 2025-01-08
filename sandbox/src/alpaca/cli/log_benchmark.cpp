#ifndef ALPACA__CLI_log_benchmark
#define ALPACA__CLI_log_benchmark

#include "alpaca/performance/logger/logger.cpp" // Alpaca::Performance::Logger
#include "cli.h"                                // Alpaca::Cli

void Alpaca::Cli::log_benchmark() {
  Alpaca::Performance::Logger logger;

  logger.log_benchmark();
}

#endif
