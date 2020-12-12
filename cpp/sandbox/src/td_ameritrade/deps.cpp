#if !defined TD_AMERITRADE_DEPENDENCIES
#define TD_AMERITRADE_DEPENDENCIES

#if !defined DEPENDENCY__NLOHMANN__JSON
#define DEPENDENCY__NLOHMANN__JSON
#include "deps/nlohmann/json.hpp" // nlohmann::json
using json = nlohmann::json;
#endif

#endif
