#ifndef DB__QUOTE_get_last_from_cache
#define DB__QUOTE_get_last_from_cache

#include "quote.h" // DB::Quote, quote_t, get_last_args_t
#include <list>    // std::list

std::list<DB::Quote::quote_t>
DB::Quote::get_last_from_cache(const get_last_args_t args) {
  const double end_at = args.end_at;
  const double start_at = args.start_at;

  std::list<quote_t> out;
  std::list<quote_t>::reverse_iterator quote;

  for (quote = this->cache.cache.rbegin(); quote != this->cache.cache.rend();
       quote++) {
    if (quote->timestamp < start_at) {
      continue;
    }

    if (quote->timestamp > end_at) {
      break;
    }

    out.push_front(*quote);
  }

  return out;
}

#endif
