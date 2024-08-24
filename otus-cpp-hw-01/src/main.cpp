#include <iostream>
#include "lib.h"

int main() {
    std::cout << "Version: " << Example::getVersion() << std::endl;
    std::cout << "Hello, World!" << std::endl;

    return 0;
}