#include "Shuffler.h"

#include <functional>
#include <limits>
#include <utility>

namespace Homework {

    Shuffler::Shuffler(std::size_t numberOfReducers_, Partitioner partitioner_) 
        : numberOfReducers(numberOfReducers_), partitioner(partitioner_) {
    }

    void Shuffler::shuffle(const std::vector<MappedData>& input, std::vector<MappedData>& output) {
        MappedData total;
        mergeMappedSections(input, total);
        populateReducers(total, output);
    }
    
    void Shuffler::mergeMappedSections(const std::vector<MappedData>& input, MappedData& output) {
        for (auto& mappedData : input) {
            for (auto& keyValue : mappedData) {
                MappedValue& value = output[keyValue.first];
                for (auto& element : keyValue.second) {
                    value.insert(element);
                }
            }
        }
    }

    void Shuffler::populateReducers(MappedData& total, std::vector<MappedData>& output) {
        output.resize(numberOfReducers);
        for (auto& keyValue : total) {
            auto paritionIndex = partitioner(keyValue.first, keyValue.second, numberOfReducers);
            output[paritionIndex].insert(std::move(keyValue));
        }
    }
    
}
