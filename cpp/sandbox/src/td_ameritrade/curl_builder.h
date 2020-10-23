#if !defined(CURL_BUILDER)
#define CURL_BUILDER

#include <map>     // std::map
#include <sstream> // std::stringstream
#include <string>  // std::string

class CurlBuilder {
public:
  struct props_t {
    std::string method;
    std::string url;
    std::map<std::string, std::string> body_params;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> query_params;
  };

  CurlBuilder(CurlBuilder::props_t props_) { props = props_; };
  std::string build();

private:
  struct request_t {
    std::string method;
    std::string body_params;
    std::string headers;
    std::string query_params;
    std::string url;
  };

  CurlBuilder::props_t props;
  CurlBuilder::request_t request;

  std::stringstream output;

  void compose();
  void init_request();
  void set_body_params();
  void set_headers();
  void set_query_params();
};
#endif
