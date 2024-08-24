#include "Reducer.h"

#include <filesystem>
#include <fstream>

namespace Homework {

    namespace {
        const std::string FILENAME = "/out-";
        const std::string FILE_EXTENSION = ".txt";
        const std::string LINE_AND_PREFIX_DELIMITER = " - ";
        const char NEWLINE = '\n';
    }

    Reducer::Reducer(const std::string& reducerName_, MappedData& input_, ReduceFunction reduce_) 
        : reducerName(reducerName_), input(std::move(input_)), reduce(reduce_) {
        
        reduceThread = std::make_unique<std::thread>([this]() { run(); });
    }

    void Reducer::join() {
        reduceThread->join();
    }

    void Reducer::run() {
        ReduceOutput output;
        for (auto& keyValue : input) {
            reduce(keyValue.first, keyValue.second, output);
        }

        writeToFile(output);
    }

    void Reducer::writeToFile(const ReduceOutput& output) {
        std::string outputFilename = std::filesystem::current_path().string() + FILENAME + reducerName + FILE_EXTENSION;
        std::ofstream file(outputFilename);
        for (auto& keyValue : output) {
            file << keyValue.first << LINE_AND_PREFIX_DELIMITER << keyValue.second << NEWLINE;
        }
        file << std::endl;
    }
}
