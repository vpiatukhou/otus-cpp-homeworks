#include "FileCommandWriter.h"

#include <chrono>
#include <fstream>

namespace Homework {

const std::string FILENAME_PREFIX = "bulk";
const std::string FILE_EXTENSION = ".log";

void FileCommandWriter::onFlush(const std::vector<std::string>& commands) {
    auto timeSinceEpoch = std::chrono::system_clock::now().time_since_epoch();
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(timeSinceEpoch).count();

    std::string filename = FILENAME_PREFIX;
    filename += std::to_string(timestamp);
    filename += FILE_EXTENSION;

    std::ofstream file(filename);
    writeToStream(file, commands);
    file.flush();
    file.close();
}

};
