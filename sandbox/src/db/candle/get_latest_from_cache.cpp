#ifndef DB__CANDLE_get_latest_from_cache
#define DB__CANDLE_get_latest_from_cache

#include "candle.h" // DB::Candle, candle_t, get_latest_args_t
#include <list>     // std::list

std::list<DB::Candle::candle_t>
DB::Candle::get_latest_from_cache(const get_latest_args_t args) {
  const double end_at = args.end_at;
  const double start_at = args.start_at;

  std::list<candle_t> out;

  for (const candle_t candle : this->cache) {
    if (candle.opened_at < start_at) {
      continue;
    }

    if (candle.closed_at > end_at) {
      break;
    }

    out.push_back(candle);
  }

  return out;
}

#endif
