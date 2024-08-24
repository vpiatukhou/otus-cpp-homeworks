#pragma once

#include "Types.h"
#include "FileReader.h"

#include <vector>
#include <string>
#include <memory>

namespace Homework {

    class Splitter {
    public:
        /**
         * @param inputFilepath_        - a path (absolute or relative) to the input file. A file contains records separated by '\n'.
         * @param numberOfPartitions_   - a number of partitions.
         *                                ATTENTION: in some case the actual number of partitions may be less than the given value.
         *                                           Please see splitInputData() for more details.
         */
        Splitter(const std::string& inputFilepath_, NumberOfPartitions numberOfPartitions_);

        /**
         * Splits the input file into partitions.
         *
         * ATTENTION: splitting may be a bit innacurate if all records are of the same length.
         *
         * E.g. a file contains four records:
         *
         * AA\nBB\nCC\nDD\n
         *
         * It will be splitted into two partitions:
         *
         * AA\nBB\nCC\n
         * DD\n
         *
         * It should not be a problem if file contains many short records.
         *
         * @return a vector of FileReaders. An each reader reads its own parition.
         *         The size of the vector equals to numberOfPartitions_
         *         ATTENTION: if the file doesn't contain enough data, the result may be less than numberOfPartitions_
         */
        std::vector<std::unique_ptr<FileReader>> splitInputData();

    private:
        std::string inputFilepath;
        NumberOfPartitions numberOfPartitions;
    };

}
