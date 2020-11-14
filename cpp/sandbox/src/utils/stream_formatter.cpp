#if !defined(STREAM_FORMATTER)
#define STREAM_FORMATTER

#include <ostream> // std::ostream
#include <string>  // std::string, std::to_string
#include <vector>  // std::vector

// Borrowed from @Joel Sjögren
// https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
class StreamFormatter {
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
    FG_RED = 31,
    FG_YELLOW = 33,
    FONT_BOLD = 1,
    RESET = 0,
  };

  friend std::ostream &operator<<(std::ostream &os,
                                  const StreamFormatter &modifier) {
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

  StreamFormatter(std::vector<code_t> codes_) : codes(codes_) {}

private:
  std::vector<code_t> codes;
};

#endif
