// TODO: Decide
#ifndef ALPACA__CLIENT_set_open_order_reversals
#define ALPACA__CLIENT_set_open_order_reversals

#include "is_non_init_reversing.cpp" // is_non_init_reversing
#include "latest_reversal_after.cpp" // latest_reversal_after
#include "tao_bot.h" // Alpaca::TaoBot, reversal_t, reversal_type_t

void Alpaca::TaoBot::set_open_order_reversals() {
  if (!this->open_order_ptr) {
    return;
  }

  if (!this->should_stop_profit) {
    return;
  }

  // TODO: Decide
  if (this->closed_positions.empty()) {
    return;
  }

  const reversal_t stop_profit_reversal_ =
      this->open_order_ptr->stop_profit_reversal;

  // TODO: Decide
  // if (this->api_client.config.should_adjust_stop_loss) {
  //   const reversal_t newer_stop_loss_reversal =
  //       latest_reversal_after(this->secondary_reversals,
  //       this->open_order_ptr-timestamp,
  //                      stop_profit_reversal_.type);

  //   if (newer_stop_loss_reversal.at && newer_stop_loss_reversal.mid) {
  //     if (this->open_order_ptr->action == order_action_t::BUY) {
  //       if (newer_stop_loss_reversal.mid >
  //           this->open_order_ptr->entry_reversal.mid) {
  //         this->open_order_ptr->entry_reversal = newer_stop_loss_reversal;
  //       }
  //     }

  //     if (this->open_order_ptr->action == order_action_t::SELL) {
  //       if (newer_stop_loss_reversal.mid <
  //           this->open_order_ptr->entry_reversal.mid) {
  //         this->open_order_ptr->entry_reversal = newer_stop_loss_reversal;
  //       }
  //     }
  //   }
  // }

  const reversal_t newer_stop_profit_reversal = latest_reversal_after(
      this->tertiary_reversals, this->open_order_ptr->timestamp,
      stop_profit_reversal_.type);

  if (newer_stop_profit_reversal.at && newer_stop_profit_reversal.mid) {
    if (this->open_order_ptr->action == order_action_t::BUY) {
      if (newer_stop_profit_reversal.mid >
          this->open_order_ptr->stop_profit_reversal.mid) {
        this->open_order_ptr->stop_profit_reversal = newer_stop_profit_reversal;
      }
    }

    if (this->open_order_ptr->action == order_action_t::SELL) {
      if (newer_stop_profit_reversal.mid <
          this->open_order_ptr->stop_profit_reversal.mid) {
        this->open_order_ptr->stop_profit_reversal = newer_stop_profit_reversal;
      }
    }
  }
}

#endif
