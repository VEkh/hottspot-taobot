#if !defined(CURL_BUILDER)
#define CURL_BUILDER

#include <curl/curl.h> // CURL, curl_easy_init
#include <map>         // std::map
#include <string>      // std::string

class CurlClient {
public:
  enum http_method_t { GET, POST };

  struct props_t {
    http_method_t method;
    std::string url;
    std::map<std::string, std::string> body_params;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> query_params;
  };

  CurlClient(CurlClient::props_t);
  void print_request();
  void request();

private:
  struct transformed_props_t {
    std::string body_params;
    std::string headers;
    std::string method;
    std::string query_params;
    std::string url;
  };

  CURL *curl = curl_easy_init();
  CurlClient::props_t props;
  CurlClient::transformed_props_t transformed_props;
  std::string HTTP_METHODS[2] = {"GET", "POST"};

  std::string build_query_params();
  std::string to_string();

  void prepare_request();
  void set_body_params();
  void set_headers();
  void set_method();
  void set_url();
};
#endif
