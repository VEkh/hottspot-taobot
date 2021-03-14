#include <iostream>

#include <map>

std::map<const char *, const char *> ICONS = {
    {"BUY", "📈"},
    {"SELL_SHORT", "📉"},
};

int main() { std::cout << ICONS["BUY"] << std::endl; }
