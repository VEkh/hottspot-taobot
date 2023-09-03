#ifndef CURL_CLIENT_request_with_retry
#define CURL_CLIENT_request_with_retry

#include "curl_client.h" // CurlClient
#include <unistd.h>      // usleep

template <typename RequestPredicate, typename ResponsePredicate>
CurlClient CurlClient::request_with_retry(RequestPredicate request_predicate,
                                          ResponsePredicate response_predicate,
                                          double maxRetries, int retry) {
  return request_with_retry(&request_predicate, &response_predicate, maxRetries,
                            retry);
}

template <typename RequestPredicate, typename ResponsePredicate>
CurlClient CurlClient::request_with_retry(RequestPredicate request_predicate,
                                          ResponsePredicate *response_predicate,
                                          double maxRetries, int retry) {
  return request_with_retry(&request_predicate, response_predicate, maxRetries,
                            retry);
}

template <typename RequestPredicate, typename ResponsePredicate>
CurlClient CurlClient::request_with_retry(RequestPredicate *request_predicate,
                                          ResponsePredicate *response_predicate,
                                          double maxRetries, int retry) {
  CurlClient curl_client = (*request_predicate)();

  if ((*response_predicate)(curl_client) && retry < maxRetries) {
    usleep(0.5 * 1e6);

    return request_with_retry(request_predicate, response_predicate, maxRetries,
                              retry + 1);
  }

  return curl_client;
}

#endif
