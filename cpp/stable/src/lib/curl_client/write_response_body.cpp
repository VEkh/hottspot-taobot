#if !defined CURL_CLIENT_write_response_body
#define CURL_CLIENT_write_response_body

#include "curl_client.h" // CurlClient, response_t
#include <string>        // std::string

size_t CurlClient::write_response_body(char *buffer, size_t size,
                                       size_t data_size, void *userdata) {
  size_t real_size = size * data_size;
  response_t *res = (response_t *)userdata;

  res->body += std::string(buffer).substr(0, real_size);
  res->size += real_size;

  return real_size;
}

#endif
