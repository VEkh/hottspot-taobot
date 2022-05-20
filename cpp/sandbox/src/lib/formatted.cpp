#ifndef FORMATTED_STREAM
#define FORMATTED_STREAM

#include <ostream> // std::ostream
#include <sstream> // std::ostringstream
#include <string>  // std::string, std::to_string
#include <vector>  // std::vector

namespace Formatted {
// Borrowed from @Joel Sjögren
// https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
class Stream {
public:
  enum code_t {
    BG_BLUE = 44,
    BG_DEFAULT = 49,
    BG_GREEN = 42,
    BG_RED = 41,
    FG_BLUE = 34,
    FG_CYAN = 36,
    FG_DEFAULT = 39,
    FG_GREEN = 32,
    FG_MAGENTA = 35,
    FG_RED = 31,
    FG_YELLOW = 33,
    FONT_BOLD = 1,
    FONT_UNDERLINE = 4,
    RESET = 0,
  };

  friend std::ostream &operator<<(std::ostream &os, const Stream &modifier) {
    std::string modifier_string;
    std::vector<code_t> codes = modifier.codes;

    for (int i = 0; i < codes.size(); i++) {
      if (i != 0) {
        modifier_string += ";";
      }

      modifier_string += std::to_string(codes[i]);
    }

    return os << "\33[" << modifier_string << "m";
  }

  Stream(std::vector<code_t> codes_) : codes(codes_){};

private:
  std::vector<code_t> codes;
};

struct fmt_stream_t {
  Stream blue;
  Stream bold;
  Stream cyan;
  Stream green;
  Stream magenta;
  Stream red;
  Stream reset;
  Stream underline;
  Stream yellow;
};

fmt_stream_t stream() {
  return {
      .blue = Stream({Stream::code_t::FG_BLUE}),
      .bold = Stream({Stream::code_t::FONT_BOLD}),
      .cyan = Stream({Stream::code_t::FG_CYAN}),
      .green = Stream({Stream::code_t::FG_GREEN}),
      .magenta = Stream({Stream::code_t::FG_MAGENTA}),
      .red = Stream({Stream::code_t::FG_RED}),
      .reset = Stream({Stream::code_t::RESET}),
      .underline = Stream({Stream::code_t::FONT_UNDERLINE}),
      .yellow = Stream({Stream::code_t::FG_YELLOW}),
  };
}

std::string error_message(std::string message) {
  fmt_stream_t fmt = stream();
  std::ostringstream output;

  output << fmt.bold << fmt.red << message << fmt.reset;

  return output.str();
}
} // namespace Formatted
#endif
