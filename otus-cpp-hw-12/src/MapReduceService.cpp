#include "MapReduceService.h"
#include "Mapper.h"
#include "Reducer.h"

#include <memory>
#include <string>
#include <utility>

namespace Homework {

    MapReduceService::MapReduceService(Splitter splitter_, Shuffler shuffler_, MapFunction mapFunction_,
        NumberOfPartitions numberOfMappers_, ReduceFunction reduceFunction_)
        : splitter(splitter_),
          shuffler(shuffler_),
          mapFunction(mapFunction_),
          numberOfMappers(numberOfMappers_),
          reduceFunction(reduceFunction_) {
    }

    void MapReduceService::start() {
        //split the given file on partitions
        auto partitions = splitter.splitInputData();

        //create and start mappers
        std::vector<std::unique_ptr<Mapper>> mappers;
        mappers.reserve(partitions.size());

        for (auto& partition : partitions) {
            mappers.push_back(std::make_unique<Mapper>(partition, mapFunction));
        }

        //wait until the mappers do their work
        for (auto& mapper : mappers) {
            mapper->join();
        }

        //shuffle
        std::vector<MappedData> shuffleInput;
        for (auto& mapper : mappers) {
            MappedData output;
            mapper->extractOutput(output);
            shuffleInput.push_back(std::move(output));
        }

        std::vector<MappedData> shuffleOutput;
        shuffler.shuffle(shuffleInput, shuffleOutput);

        //create and start reducers
        std::vector<std::unique_ptr<Reducer>> reducers;
        reducers.reserve(shuffleOutput.size());
        std::size_t reducerNumber = 1;
        for (auto& reducerInput : shuffleOutput) {
            reducers.push_back(std::make_unique<Reducer>(std::to_string(reducerNumber), reducerInput, reduceFunction));
            ++reducerNumber;
        }

        //wait for the result
        for (auto& reducer : reducers) {
            reducer->join();
        }
    }
}