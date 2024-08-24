#include "ConsoleCommandWriter.h"

#include <iostream>

namespace Homework {

void ConsoleCommandWriter::onFlush(const std::vector<std::string>& commands) {
    writeToStream(std::cout, commands);
    std::cout << std::endl;
}

};
