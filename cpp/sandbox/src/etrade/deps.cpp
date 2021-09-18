#ifndef ETRADE_DEPENDENCIES
#define ETRADE_DEPENDENCIES

#ifndef DEPENDENCY__CPP_BASE64__BASE64
#define DEPENDENCY__CPP_BASE64__BASE64
#include "deps/cpp-base64/base64.cpp" // base64_encode
#endif

#ifndef DEPENDENCY__NLOHMANN__JSON
#define DEPENDENCY__NLOHMANN__JSON
#include "deps/nlohmann/json.hpp" // nlohmann::json
using json = nlohmann::json;
#endif

// Package: openssl
#ifndef DEPENDENCY__OPENSSL__EVP
#define DEPENDENCY__OPENSSL__EVP
#include <openssl/evp.h> // EVP_MAX_MD_SIZE
#endif

#ifndef DEPENDENCY__OPENSSL__HMAC
#define DEPENDENCY__OPENSSL__HMAC
#include <openssl/hmac.h> // HMAC
#endif

#ifndef DEPENDENCY__OPENSSL__SHA
#define DEPENDENCY__OPENSSL__SHA
#include <openssl/sha.h> // SHA1, SHA_DIGEST_LENGTH
#endif

#endif
