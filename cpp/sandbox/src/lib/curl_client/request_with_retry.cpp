#if !defined CURL_CLIENT_request_with_retry
#define CURL_CLIENT_request_with_retry

#include "curl_client.h" // CurlClient
#include <string>        // std::string

template <typename RequestPredicate, typename ResponsePredicate>
CurlClient
CurlClient::request_with_retry(RequestPredicate request_predicate,
                               ResponsePredicate response_predicate) {
  return request_with_retry(&request_predicate, &response_predicate);
}

template <typename RequestPredicate, typename ResponsePredicate>
CurlClient
CurlClient::request_with_retry(RequestPredicate request_predicate,
                               ResponsePredicate *response_predicate) {
  return request_with_retry(&request_predicate, response_predicate);
}

template <typename RequestPredicate, typename ResponsePredicate>
CurlClient
CurlClient::request_with_retry(RequestPredicate *request_predicate,
                               ResponsePredicate *response_predicate) {
  CurlClient curl_client = (*request_predicate)();

  if ((*response_predicate)(curl_client.response.body)) {
    return request_with_retry(request_predicate, response_predicate);
  }

  return curl_client;
}

#endif
