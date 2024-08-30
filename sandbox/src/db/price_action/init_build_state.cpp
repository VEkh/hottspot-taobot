#ifndef DB__PRICE_ACTION_init_build_state
#define DB__PRICE_ACTION_init_build_state

#include "latest_opened_at.cpp" // latest_opened_at
#include "price_action.h"       // DB::PriceAction, build_args_t
#include <string>               // std::stod
#include <time.h>               // time

void DB::PriceAction::init_build_state(const build_args_t args) {
  this->build_state = {
      .end_at = (double)time(nullptr),
      .start_at = 0.0,
      .timer_start = (double)time(nullptr),
  };

  if (!args.end_at.empty()) {
    this->build_state.end_at =
        this->db_utils.timestamp_to_epoch(args.end_at, "UTC");
  }

  if (args.start_at.empty()) {
    this->build_state.start_at = latest_opened_at();
  } else {
    this->build_state.start_at =
        args.start_at == "earliest"
            ? 0.0
            : this->db_utils.timestamp_to_epoch(args.start_at, "UTC");
  }
}

#endif
