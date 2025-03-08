// TODO: Decide
#ifndef ALPACA__TAO_BOT_update_inverted_reversal
#define ALPACA__TAO_BOT_update_inverted_reversal

#include "first_reversal_after.cpp" // first_reversal_after
#include "tao_bot.h"                // Alpaca::TaoBot, order_t, reversal_t

void Alpaca::TaoBot::update_inverted_reversal(order_t *order) {
  const reversal_t reversal = order->entry_reversal;

  if (!reversal.is_inverted) {
    return;
  }

  const reversal_t newer_reversal =
      first_reversal_after(this->reversals, reversal.at, reversal.type);

  if (newer_reversal.at > reversal.at) {
    order->entry_reversal = newer_reversal;
  }
}

#endif
