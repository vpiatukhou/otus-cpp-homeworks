#pragma once

#include "Types.h"

#include <memory>
#include <string>
#include <thread>

namespace Homework {

    class Reducer {
    public:
        Reducer(const std::string& reducerName_, MappedData& input_, ReduceFunction reduce_);
        Reducer(const Reducer&) = delete;
        Reducer(Reducer&&) = delete;
        ~Reducer() = default;

        Reducer& operator=(const Reducer&) = delete;
        Reducer& operator=(Reducer&&) = delete;

        void join();
    private:
        std::string reducerName;
        MappedData input;
        ReduceFunction reduce;
        std::string outputFilename;
        std::unique_ptr<std::thread> reduceThread;

        void run();
        void writeToFile(const ReduceOutput& output);
    };
}
