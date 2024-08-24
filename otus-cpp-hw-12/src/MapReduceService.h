#pragma once

#include "Shuffler.h"
#include "Splitter.h"
#include "Types.h"

namespace Homework {

    class MapReduceService {
    public:
        MapReduceService(Splitter splitter,
                         Shuffler shuffler_,
                         MapFunction mapFunction_,
                         NumberOfPartitions numberOfMappers_,
                         ReduceFunction reduceFunction_);

        /**
         * Start MapReduce tasks.
         *
         * The result will be written into files the current working directory.
         *
         * The names of the files follow the pattern: "out-NUMBER_OF_PARTITIONS.txt".
         */
        void start();
    private:
        Splitter splitter;
        Shuffler shuffler;

        MapFunction mapFunction;
        NumberOfPartitions numberOfMappers;
        ReduceFunction reduceFunction;
    };
}
