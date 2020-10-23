#include "src/utils/debugger.cpp" // utils::debugger::inspect
#include "src/utils/string.cpp"   // utils::string::split
#include "src/utils/uri.cpp"      // utils::string::percentEncode
#include <sstream>                // std::stringstream
#include <string>                 // std::string

int main() {
  std::stringstream url;
  url << "https://auth.tdameritrade.com/auth?response_type=code"
      << "&redirect_uri=" << utils::uri::percentEncode("https://127.0.0.1")
      << "&client_id="
      << "%40AMER.OAUTHAP";

  utils::debugger::inspect(url.str());

  const char *code = "";

  utils::debugger::inspect(utils::uri::percentDecode(code));
}
