#include "Splitter.h"
#include "Types.h"

#include <cmath>
#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace Homework {

    namespace {
        const char LINE_DELIMITER = '\n';
    }

    Splitter::Splitter(const std::string& inputFilepath_, NumberOfPartitions numberOfPartitions_)
        : inputFilepath(inputFilepath_), numberOfPartitions(numberOfPartitions_) {
    }

    std::vector<std::unique_ptr<FileReader>> Splitter::splitInputData() {
        std::vector<std::unique_ptr<FileReader>> result;
        result.reserve(numberOfPartitions);

        FilePosition fileSize = std::filesystem::file_size(inputFilepath);
        if (fileSize == 0) {
            return result;
        }

        if (numberOfPartitions == 1) {
            result.push_back(std::make_unique<FileReader>(inputFilepath, 0, fileSize));
            return result;
        }

        auto partitionSizeAsDouble = std::ceil(static_cast<double>(fileSize) / numberOfPartitions);
        auto partitionSize = static_cast<FilePosition>(partitionSizeAsDouble);

        std::ifstream file(inputFilepath);

        FilePosition partitionBegin = 0;
        FilePosition partitionEnd = 0;

        //The actual number of paritions can be less than the given "numberOfPartitions".
        //This is why we stop the loop if partitionEnd equals to fileSize
        while (partitionEnd < fileSize) {
            //Calculate an estimated end position of the partition.
            //This is an approximate value which will be adjusted later
            partitionEnd += partitionSize;
            if (partitionEnd > fileSize) {
                partitionEnd = fileSize;
            } else {
                //set the cursor to the estimated end of the section
                file.seekg(partitionEnd);

                //move the cursor to the actual end of the section
                file.ignore(fileSize - partitionEnd, LINE_DELIMITER);
                if (file.eof()) {
                    partitionEnd = fileSize;
                } else {
                    partitionEnd = file.tellg();
                    if (partitionEnd == -1) {
                        throw std::runtime_error("Error reading the file.");
                    }
                }
            }

            result.push_back(std::make_unique<FileReader>(inputFilepath, partitionBegin, partitionEnd));
            partitionBegin = partitionEnd;
        }

        return result;
    }
}
