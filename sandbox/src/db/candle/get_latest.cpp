#ifndef DB__CANDLE_get_latest
#define DB__CANDLE_get_latest

#include "candle.h"                  // DB::Candle, get_latest_args_t
#include "get_latest_from_cache.cpp" // get_latest_from_cache
#include "get_latest_from_db.cpp"    // get_latest_from_db
#include <list>                      // std::list

std::list<DB::Candle::candle_t>
DB::Candle::get_latest(const get_latest_args_t args) {
  return args.read_cache ? get_latest_from_cache(args)
                         : get_latest_from_db(args);
}

#endif
