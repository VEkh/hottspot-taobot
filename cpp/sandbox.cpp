#include "deps/cpp-base64/base64.cpp"
#include <algorithm>   // std::transform
#include <curl/curl.h> // curl_easy_escape, curl_easy_init
#include <cxxabi.h>
#include <iomanip>
#include <iostream>
#include <openssl/engine.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <sstream>
#include <string.h>

/* NOTE:
 * No need to use all the init mumbo jumbo
 * It does seem that the strings need to be converted to that hex byte thingy
 * HMAC is returning the same result with escaped hex string literals as normal
 * strings for `data` and `key`
 */

/* What I've learned:
 * The unsigned char arr is a sequence of hexadecimal codes
 * Each hexadecimal code corresponds to an ASCII code
 */

int main() {
  std::string key = "kd94hf93k423kf44&pfkkdhi9sl3r4s00";
  std::string data =
      "GET&http%3A%2F%2Fphotos.example.net%2Fphotos&file%3Dvacation.jpg%"
      "26oauth_consumer_key%3Ddpf43f3p2l4k3l03%26oauth_nonce%"
      "3Dkllo9940pd9333jh%26oauth_signature_method%3DHMAC-SHA1%26oauth_"
      "timestamp%3D1191242096%26oauth_token%3Dnnch734d00sl2jdk%26oauth_version%"
      "3D1.0%26size%3Doriginal";

  unsigned char output[EVP_MAX_MD_SIZE];
  unsigned int output_length;

  HMAC(EVP_sha1(), key.c_str(), key.length(), (unsigned char *)data.c_str(),
       data.length(), output, &output_length);

  std::cout << output << std::endl;
  std::cout << output_length << std::endl;

  std::stringstream output_stream;

  for (int i = 0; i < output_length; i++) {
    std::cout << output[i] << " | " << (unsigned int)output[i] << std::endl;
    output_stream << output[i];
  }

  // for (int i = 0; i < output_length; i++) {
  //   std::cout << output[i] << " | " << (unsigned int)output[i] << std::endl;
  //   output_stream << output[i];
  // }

  std::cout << "output stream length: " << output_stream.str().length()
            << std::endl;
  std::cout << "base64_encoded output (cast to string): "
            << base64_encode((std::string)((char *)output)) << std::endl;

  std::cout << "base64_encoded output (streamed to string): "
            << base64_encode(output_stream.str()) << std::endl;

  return 0;
}

/* int main() { */
/*   std::string key = "kd94hf93k423kf44&pfkkdhi9sl3r4s00"; */
/*   std::string data = */
/*       "GET&http%3A%2F%2Fphotos.example.net%2Fphotos&file%3Dvacation.jpg%" */
/*       "26oauth_consumer_key%3Ddpf43f3p2l4k3l03%26oauth_nonce%" */
/*       "3Dkllo9940pd9333jh%26oauth_signature_method%3DHMAC-SHA1%26oauth_" */
/*       "timestamp%3D1191242096%26oauth_token%3Dnnch734d00sl2jdk%26oauth_version%"
 */
/*       "3D1.0%26size%3Doriginal"; */

/*   unsigned char output[EVP_MAX_MD_SIZE]; */
/*   unsigned int output_length; */

/*   HMAC(EVP_sha1(), key.c_str(), key.length(), (unsigned char *)data.c_str(),
 */
/*        data.length(), output, &output_length); */

/*   /1* NOTE: You may not have to do this per
 * https://oauth.net/core/1.0/#anchor31 */
/*    *1/ */
/*   std::stringstream ss; */
/*   ss << std::hex << std::setw(2) << std::setfill('0'); */

/*   for (int i = 0; i < output_length; ++i) { */
/*     ss << (unsigned int)output[i]; */
/*   } */

/*   std::string final_hash = ss.str(); */

/*   std::cout << "output: " << base64_encode((std::string)((char *)output)) */
/*             << std::endl; */
/*   std::cout << base64_encode(final_hash) << std::endl; */

/*   return 0; */
/* } */

std::string uriEscape(const char *str) {
  if (str == NULL) {
    return "";
  }

  CURL *curl = curl_easy_init();
  const char *escaped = curl_easy_escape(curl, str, strlen(str));

  return (std::string)escaped;
}

// int main() {
//   std::string str = base64_decode("tR3+Ty81lMeYAr/Fid0kMTYa/WM=");
//   std::string str1 = base64_decode("tR3+Ty81lMeYAr/Fid0kMTYa/WPvfw==");

//   for (int i = 0; i < str.length(); i++) {
//     std::cout << str.at(i) << " | " << (int)str.at(i) << std::endl;
//   }

//   std::cout << base64_encode(str) << std::endl;
//   std::cout << "string length: " << str.length() << std::endl;
// }
