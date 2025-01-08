#ifndef ALPACA__CLI_cancel_orders
#define ALPACA__CLI_cancel_orders

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "cli.h"                    // Alpaca::Cli, fmt
#include "lib/formatted.cpp"        // Formatted
#include <iostream>                 // std::cout, std::endl
#include <stdexcept>                // std::invalid_argument
#include <stdio.h>                  // printf
#include <string>                   // std::string

void Alpaca::Cli::cancel_orders() {
  if (this->args.empty()) {
    const std::string message =
        Formatted::error_message("Please provide at least one order id.");

    throw std::invalid_argument(message);
  }

  Alpaca::Client api_client(this->flags);

  for (const std::string arg : this->args) {
    const std::string response = api_client.cancel_order(arg);

    std::cout << fmt.bold << fmt.yellow;
    printf("Cancel Response: %s", response.c_str());
    std::cout << fmt.reset << std::endl;

    if (response.empty()) {
      std::cout << fmt.bold << fmt.green;
      printf("👍🏾Successfully cancelled order: %s", arg.c_str());
      std::cout << fmt.reset << std::endl;
    }
  }
}

#endif
