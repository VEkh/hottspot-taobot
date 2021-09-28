#ifndef ETRADE__TAO_BOT_loss_to_recover
#define ETRADE__TAO_BOT_loss_to_recover

/*
 * ETrade::TaoBot
 * closed_positions_stats_t
 */
#include "tao_bot.h"

#include "build_closed_positions_stats.cpp" // build_closed_positions_stats

double ETrade::TaoBot::loss_to_recover() {
  const closed_positions_stats_t stats = build_closed_positions_stats();

  return stats.current_balance - stats.max_balance;
}

#endif
