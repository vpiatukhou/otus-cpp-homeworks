/**
 * Contains aliases for types which are used in many places in the program.
 */
#include <string>
#include <unordered_set>
#include <map>
#include <iosfwd>
#include <functional>

namespace Homework {

    using MappedKey = std::string;
    using MappedValue = std::unordered_set<std::string>;
    using MappedData = std::map<MappedKey, MappedValue>;

    /**
     * A number of mapper and reducer threads.
     */
    using NumberOfPartitions = unsigned int;

    /**
     * A position in the file.
     */
    using FilePosition = std::streampos;

    using Partitioner = std::function<std::size_t(const MappedKey&, const MappedValue&, NumberOfPartitions)>;

    using MapFunction = std::function<void(const MappedKey&, MappedData&)>;

    using ReduceOutput = std::map<MappedKey, std::string>;
    using ReduceFunction = std::function<void(const MappedKey&, const MappedValue&, ReduceOutput&)>;
}
