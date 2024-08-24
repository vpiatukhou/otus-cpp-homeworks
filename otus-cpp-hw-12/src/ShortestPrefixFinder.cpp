#include "ShortestPrefixFinder.h"

#include <boost/container_hash/hash.hpp>

namespace Homework {
    
    void map(const MappedKey& key, MappedData& output) {
        MappedValue value;
        for (std::size_t i = 1; i <= key.size(); ++i) {
            auto prefix = key.substr(0, i);
            output[prefix].insert(std::move(key));
        }
    }

    void reduce(const MappedKey& key, const MappedValue& value, ReduceOutput& output) {
        if (value.size() == 1) {
            auto valueIt = value.begin();
            auto outputIt = output.find(*valueIt);
            if (outputIt == output.end()) {
                output[*valueIt] = key;
            }
        }
    }

    std::size_t getPartition(const MappedKey&, const MappedValue& value, std::size_t numberOfPartitions) {
        auto hash = boost::hash_unordered_range(value.begin(), value.end());
        return (hash + std::numeric_limits<std::size_t>::max()) % numberOfPartitions;
    }
}