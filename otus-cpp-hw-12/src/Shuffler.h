#pragma once

#include "Types.h"

#include <vector>

namespace Homework {

    class Shuffler {
    public:
        Shuffler(std::size_t numberOfReducers_, Partitioner partitioner_);

        /**
         * Merges and sorts data, produced by mappers.
         * Distribute data between reducers.
         * 
         * @param input  - result of mappers
         * @param output - data for reducers
         */
        void shuffle(const std::vector<MappedData>& input, std::vector<MappedData>& output);
    private:
        Partitioner partitioner;
        std::size_t numberOfReducers;

        void mergeMappedSections(const std::vector<MappedData>& input, MappedData& output);
        void populateReducers(MappedData& total, std::vector<MappedData>& output);
    };

}
