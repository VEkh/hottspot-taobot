#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include <fstream> // std::ifstream
#include <string>  //std::getline, std::string

enum actions { BUY, SELL };

int main() { printf("action: %i\n", actions::SELL); }
