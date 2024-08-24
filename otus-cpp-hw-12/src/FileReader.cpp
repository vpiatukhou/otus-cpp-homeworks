#include "FileReader.h"

#include <boost/algorithm/string/trim.hpp>

namespace Homework {

    FileReader::FileReader(const std::string& inputFilepath_, FilePosition startPosition_, FilePosition endPosition_)
        : file(inputFilepath_), endPosition(endPosition_) {

        file.seekg(startPosition_);
    }

    void FileReader::readLine(std::string& line) {
        std::getline(file, line);
        boost::trim(line);
    }

    bool FileReader::hasNext() {
        return !file.eof() && file.tellg() < endPosition;
    }

    FilePosition FileReader::getEndPosition() const {
        return endPosition;
    }
}
