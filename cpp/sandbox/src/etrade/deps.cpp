#if !defined ETRADE_DEPENDENCIES
#define ETRADE_DEPENDENCIES

#if !defined DEPENDENCY__CPP_BASE64__BASE64
#define DEPENDENCY__CPP_BASE64__BASE64
#include "deps/cpp-base64/base64.cpp" // base64_encode
#endif

#if !defined DEPENDENCY__NLOHMANN__JSON
#define DEPENDENCY__NLOHMANN__JSON
#include "deps/nlohmann/json.hpp" // nlohmann::json
using json = nlohmann::json;
#endif

#if !defined DEPENDENCY__LIBXMLPP
#define DEPENDENCY__LIBXMLPP
// http://libxmlplusplus.sourceforge.net/
#include <libxml++/libxml++.h> // xmlpp::DomParser
#endif

// Package: openssl
#if !defined DEPENDENCY__OPENSSL__EVP
#define DEPENDENCY__OPENSSL__EVP
#include <openssl/evp.h> // EVP_MAX_MD_SIZE
#endif

#if !defined DEPENDENCY__OPENSSL__HMAC
#define DEPENDENCY__OPENSSL__HMAC
#include <openssl/hmac.h> // HMAC
#endif

#if !defined DEPENDENCY__OPENSSL__SHA
#define DEPENDENCY__OPENSSL__SHA
#include <openssl/sha.h> // SHA1, SHA_DIGEST_LENGTH
#endif

#endif
