#if !defined(CURL_BUILDER)
#define CURL_BUILDER

#include <curl/curl.h> // CURL, curl_easy_init
#include <map>         // std::map
#include <string>      // std::string

class CurlClient {
public:
  enum debug_t { OFF, ON };
  enum http_method_t { GET, POST };

  struct props_t {
    std::map<std::string, std::string> body_params;
    debug_t debug_flag;
    std::map<std::string, std::string> headers;
    http_method_t method;
    std::map<std::string, std::string> query_params;
    std::string url;
  };

  struct response_t {
    std::string body;
    size_t size;
  };

  CurlClient(CurlClient::props_t);

  CurlClient::response_t response;

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

  static size_t write_response(char *, size_t, size_t, void *);

  std::string HTTP_METHODS[2] = {"GET", "POST"};
  std::string build_query_params();
  std::string to_string();

  void prepare_request();
  void set_body_params();
  void set_debug();
  void set_headers();
  void set_method();
  void set_url();
};
#endif
