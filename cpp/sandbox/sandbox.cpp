#include "deps/simdjson/simdjson.cpp"
#include <iostream> // std::cout

int main() {
  auto cars_json = R"(
    { "make": "Toyota", "model": "Camry",  "year": 2018, "tire_pressure": [ 40.1, 39.9, 37.7, 40.4 ] }
  )"_padded;

  simdjson::dom::parser parser;

  simdjson::dom::element tweets;
  auto error = parser.parse(cars_json).get(tweets);
  if (error) {
    std::cerr << error << std::endl;
    return EXIT_FAILURE;
  }

  simdjson::dom::element res;
  error = tweets["blah"]["count"].get(res);

  if (error) {
    std::cerr << "could not access keys" << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << res << " results." << std::endl;
}
