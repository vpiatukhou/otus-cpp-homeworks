/**
 * Declares map and reduce functions for solving a problem about the sortest unique prefix.
 */
#pragma once

#include "Types.h"

namespace Homework {

    /**
     * 1. Create all possible prefixes for the given key.
     *    E.g. if the given line is "abcd", the prefixes are:
     *
     *    a
     *    ab
     *    abc
     *    abcd
     *
     * 2. Addeds the prefixes to the output.
     * 
     * @param key    - a line of text
     * @param output - a mapping: key=the prefix, value=the matched lines of the text
     */
    void map(const MappedKey& key, MappedData& output);

    /**
     * If there is only one email for the prefix, adds the email-prefix pair to the output
     * 
     * @param key    - a prefix which was created on "map" step
     * @param value  - lines of text that match to the prefix
     */
    void reduce(const MappedKey& key, const MappedValue& value, ReduceOutput& output);

    /**
     * @param value              - lines of text that match to the prefix
     * @param numberOfPartitions - a number of partitions
     * @return a partition depending on the value
     */
    std::size_t getPartition(const MappedKey&, const MappedValue& value, std::size_t numberOfPartitions);
}
