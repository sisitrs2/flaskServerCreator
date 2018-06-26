#include <iostream>
#include "Website.h"

int main() {
    std::string path;
    std::cout << "Enter website path (for current enter \"./\"): ";
    std::cin >> path;
    Website a(path.c_str());
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

