#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "lib/utils/float.cpp" // ::utils::float_
#include "order_duration.cpp"  // order_duration
#include "tao_bot.h"           // Alpaca::TaoBot
#include "volatility.cpp"      // volatility
#include <math.h>              // abs, pow

// TODO: Decide
#include "current_mid.cpp" // current_mid
#include <algorithm>       // std::max, std::min

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double static_one_sec_variance = this->avg_one_sec_variances.running;
  const double trailing_stop_profit_ratio = 1 / 1.1;

  double stop_loss_ratio = this->api_client.config.stop_loss_ratio;
  double stop_profit_ratio = this->api_client.config.stop_profit_ratio;

  if (this->api_client.config.stop_loss_ratios[this->symbol]) {
    stop_loss_ratio = this->api_client.config.stop_loss_ratios[this->symbol];
  }

  if (this->api_client.config.should_use_alt_stop_loss) {
    stop_loss_ratio = this->api_client.config.alt_stop_loss_ratio;
  }

  // TODO: Decide
  if (this->api_client.config.is_stop_loss_decayed) {
    const double order_duration_ = order_duration(this->open_order_ptr);

    const double stop_loss_multiplier = ::utils::float_::sigmoid({
        .decay_rate = -1.0e-2,
        .max = 1,
        .min = 0.25,
        .x = order_duration_,
        .x_shift = 300,
    });

    stop_loss_ratio = stop_loss_ratio * stop_loss_multiplier;
  }

  if (this->api_client.config.should_expand_stop_loss &&
      this->performance.loss_streaks.longest) {
    // TODO: Decide
    int multiplier = 0;

    std::map<int, int>::iterator it =
        this->performance.loss_streaks.counts.begin();

    for (; it != this->performance.loss_streaks.counts.end(); it++) {
      multiplier += it->first * it->second;
    }

    stop_loss_ratio *= log(multiplier + 3);
  }

  double stop_loss = stop_loss_ratio * static_one_sec_variance;

  const double stop_loss_percent = this->api_client.config.stop_loss_percent;

  // TODO: Decide
  if (stop_loss_percent) {
    stop_loss =
        (stop_loss_percent / 100.0) * this->open_order_ptr->execution_price;
  }

  // TODO: Decide
  // if (this->api_client.config.should_await_consolidation_indicator &&
  //     this->open_order_ptr->consolidation_range.opened_at) {
  //   const range_t consolidation_range =
  //       this->open_order_ptr->consolidation_range;

  //   const double execution_price = this->open_order_ptr->execution_price;
  //   const double high = consolidation_range.high;
  //   const double low = consolidation_range.low;
  //   const double trigger_padding = 15 * static_one_sec_variance;

  //   const double high_delta = abs(execution_price - high);
  //   const double low_delta = abs(execution_price - low);
  //   const double smaller_delta = std::min(high_delta, low_delta);

  //   stop_loss = -(smaller_delta + trigger_padding);
  // }

  // TODO: Decide
  // if (this->api_client.config.should_await_consolidation_indicator &&
  //     this->open_order_ptr->consolidation_range.opened_at) {
  //   const range_t consolidation_range =
  //       this->open_order_ptr->consolidation_range;

  //   const double execution_price = this->open_order_ptr->execution_price;
  //   const double high = consolidation_range.high;
  //   const double low = consolidation_range.low;

  //   const double high_delta = abs(execution_price - high);
  //   const double low_delta = abs(execution_price - low);
  //   const double larger_delta = std::max(high_delta, low_delta);

  //   stop_loss = -larger_delta;
  // }

  // TODO: Decide
  if (this->api_client.config.should_await_reversal_indicator &&
      this->api_client.config.is_stop_loss_dynamic) {
    const double execution_price = this->open_order_ptr->execution_price;
    const double reversal_price = this->open_order_ptr->reversal.mid;

    const double reversal_delta = abs(execution_price - reversal_price);

    const double dynamic_loss =
        reversal_delta ? reversal_delta : abs(stop_loss);

    if (this->api_client.config.is_stop_loss_true_dynamic) {
      stop_loss = -dynamic_loss;

      if (this->is_trending) {
        stop_loss =
            std::min(stop_loss, stop_loss_ratio * static_one_sec_variance);
      }

    } else {
      stop_loss = -std::min(dynamic_loss, abs(stop_loss));
    }
  }

  if (this->api_client.config.stop_profit_ratios[this->symbol]) {
    stop_profit_ratio =
        this->api_client.config.stop_profit_ratios[this->symbol];
  }

  if (this->api_client.config.is_stop_profit_decayed) {
    const double current_profit =
        std::max(10.0 * static_one_sec_variance, this->open_order_ptr->profit);

    const double multiplier =
        stop_loss ? 1.0 / abs(2.0 * current_profit / stop_loss) : 1.0;

    const double max_profit_duration =
        order_duration(this->open_order_ptr, "max_profit");

    const double x = multiplier * max_profit_duration;

    stop_profit_ratio = ::utils::float_::sigmoid({
        .decay_rate = -1e-2,
        .max = 20.0,
        .min = 1e-4,
        .x = x,
        .x_shift = 3 * 60,
    });
  }

  // TODO: Decide
  if (this->api_client.config.should_use_alt_stop_profit) {
    stop_profit_ratio = this->api_client.config.alt_stop_profit_ratio;
  }

  double stop_profit = abs(stop_profit_ratio * stop_loss);

  if (this->api_client.config.deficit_reclaim_ratio) {
    const double asset_deficit =
        abs(this->performance.current_balance - this->performance.max_balance);

    const double deficit_profit =
        1.04 * (asset_deficit / this->open_order_ptr->quantity);

    if (asset_deficit && deficit_profit >= abs(stop_loss)) {
      const double deficit_reclaim_ratio =
          this->api_client.config.deficit_reclaim_ratio;

      std::valarray<double> stop_profits = {
          deficit_reclaim_ratio * this->bulk_candle.range(), deficit_profit};

      stop_profit = stop_profits.min();
    }
  }

  double adjusted_stop_profit = stop_profit / trailing_stop_profit_ratio;

  double trailing_stop_profit =
      this->open_order_ptr->max_profit * trailing_stop_profit_ratio;

  // TODO: Decide
  // if (this->api_client.config.should_await_consolidation_indicator &&
  //     this->open_order_ptr->consolidation_range.opened_at) {
  //   const range_t consolidation_range =
  //       this->open_order_ptr->consolidation_range;

  //   const double execution_price = this->open_order_ptr->execution_price;
  //   const double high = consolidation_range.high;
  //   const double low = consolidation_range.low;
  //   const double trigger_padding = 15 * static_one_sec_variance;

  //   const double high_delta = abs(execution_price - high);
  //   const double low_delta = abs(execution_price - low);
  //   const double larger_delta = std::max(high_delta, low_delta);

  //   const double max_profit = this->open_order_ptr->max_profit;

  //   if (execution_price > high || execution_price < low) {
  //     adjusted_stop_profit = 0;
  //     trailing_stop_profit = 0;
  //   } else if (max_profit > larger_delta) {
  //     adjusted_stop_profit = max_profit;
  //     trailing_stop_profit = larger_delta - trigger_padding;
  //   }
  // }

  // TODO: Decide
  // if (this->api_client.config.should_await_reversal_indicator &&
  //     this->open_order_ptr->reversal.mid) {
  //   const double execution_price = this->open_order_ptr->execution_price;
  //   const double max_profit = this->open_order_ptr->max_profit;
  //   const double opening_reversal_mid = this->open_order_ptr->reversal.mid;
  //   const double profit_reclaim_ratio =
  //       this->api_client.config.profit_reclaim_ratio;

  //   const order_action_t action = this->open_order_ptr->action;

  //   if (action == order_action_t::BUY) {
  //     const double max_mid = execution_price + max_profit;
  //     const double trailing_stop_mid =
  //         profit_reclaim_ratio * (max_mid - opening_reversal_mid) +
  //         opening_reversal_mid;

  //     trailing_stop_profit = trailing_stop_mid - execution_price;
  //   } else {
  //     const double max_mid = execution_price - max_profit;
  //     const double trailing_stop_mid =
  //         opening_reversal_mid -
  //         profit_reclaim_ratio * (opening_reversal_mid - max_mid);

  //     trailing_stop_profit = execution_price - trailing_stop_mid;
  //   }

  //   adjusted_stop_profit = max_profit;
  // }

  return {
      .stop_loss = stop_loss,
      .stop_profit = adjusted_stop_profit,
      .trailing_stop_profit = trailing_stop_profit,
  };
}

#endif
