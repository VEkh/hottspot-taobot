#if !defined TD_AMERITRADE_DEPENDENCIES
#define TD_AMERITRADE_DEPENDENCIES

#if !defined DEPENDENCY_NLOHMANN_JSON
#define DEPENDENCY_NLOHMANN_JSON
#include "deps/nlohmann/json.hpp" // nlohmann::json
using json = nlohmann::json;
#endif

#endif
