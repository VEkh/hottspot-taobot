#ifndef DB__QUOTE_get_last
#define DB__QUOTE_get_last

#include "get_last_from_cache.cpp" // get_last_from_cache
#include "get_last_from_db.cpp"    // get_last_from_db
#include "quote.h"                 // DB::Quote, get_last_args_t, quote_t

std::list<DB::Quote::quote_t> DB::Quote::get_last(get_last_args_t args) {
  return args.read_cache ? get_last_from_cache(args) : get_last_from_db(args);
}

#endif
