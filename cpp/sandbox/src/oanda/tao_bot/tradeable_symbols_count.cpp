#ifndef OANDA__TAO_BOT_tradeable_symbols_count
#define OANDA__TAO_BOT_tradeable_symbols_count

#include "tao_bot.h" // Oanda::TaoBot
#include <fstream>   // std::ifstream, std::ios
#include <string>    //std::getline, std::string

int Oanda::TaoBot::tradeable_symbols_count() {
  const std::string symbols_file_path =
      std::string(APP_DIR) + "/bin/oanda/symbols";

  std::ifstream file(symbols_file_path.c_str(), std::ios::in);

  int count = 0;
  std::string line;

  while (std::getline(file, line)) {
    count++;
  }

  return count;
}

#endif
