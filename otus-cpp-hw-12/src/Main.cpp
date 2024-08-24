#include "MapReduceService.h"
#include "ShortestPrefixFinder.h"
#include "Shuffler.h"
#include "Splitter.h"

#include <cctype>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <iostream>

namespace Homework {

    namespace {
        const std::uint8_t NUMBER_OF_ARGUMENTS = 4;
        const std::uint8_t INPUT_FILE_ARG_INDEX = 1;
        const std::uint8_t NUM_OF_MAPPERS_ARG_INDEX = 2;
        const std::uint8_t NUM_OF_REDUCERS_ARG_INDEX = 3;

        const std::uint8_t VALIDATION_ERROR = -1;
        const std::string INVALID_NUM_OF_THREADS_ARG = " must be a positive integer number.";
    }

    NumberOfPartitions stringToNumberOfThreads(const std::string& value) {
        for (auto& ch : value) {
            if (!std::isdigit(ch)) {
                throw std::invalid_argument(INVALID_NUM_OF_THREADS_ARG);
            }
        }
        NumberOfPartitions numeric;
        try {
            numeric = std::stoi(value);
        } catch (std::logic_error&) {
            throw std::invalid_argument(INVALID_NUM_OF_THREADS_ARG);
        }

        if (numeric == 0) {
            throw std::invalid_argument(INVALID_NUM_OF_THREADS_ARG);
        }
        return numeric;
    }

}

int main(int argc, char* argv[]) {
    using namespace Homework;

    if (argc < NUMBER_OF_ARGUMENTS) {
        std::cerr << "'mapreduce' requires 3 arguments.\n\nUsage:\tmapreduce INPUT_FILE NUMBER_OF_MAPPER_THREADS NUMBER_OF_REDUCER_THREADS\n" << std::endl;
        return VALIDATION_ERROR;
    }

    std::string inputFile = argv[INPUT_FILE_ARG_INDEX];
    NumberOfPartitions numberOfMappers;
    NumberOfPartitions numberOfReducers;

    if (!std::filesystem::is_regular_file(inputFile)) {
        std::cerr << "There is no file with the given path." << std::endl;
        return VALIDATION_ERROR;
    }

    try {
        numberOfMappers = stringToNumberOfThreads(argv[NUM_OF_MAPPERS_ARG_INDEX]);
    } catch (std::invalid_argument& e) {
        std::cerr << "NUMBER_OF_MAPPER_THREADS" << e.what() << std::endl;
        return VALIDATION_ERROR;
    }

    try {
        numberOfReducers = stringToNumberOfThreads(argv[NUM_OF_REDUCERS_ARG_INDEX]);
    } catch (std::invalid_argument& e) {
        std::cerr << "NUMBER_OF_REDUCER_THREADS" << e.what() << std::endl;
        return VALIDATION_ERROR;
    }

    Splitter splitter(inputFile, numberOfMappers);
    Shuffler shuffler(numberOfReducers, getPartition);
    MapReduceService mapReduceService(splitter, shuffler, map, numberOfMappers, reduce);
    mapReduceService.start();

    return 0;
}
