#include "Shuffler.h"

#include "gmock/gmock.h"

namespace {
    using namespace Homework;
    using ::testing::UnorderedElementsAre;

    std::size_t simplePartitioner(const std::string& key, const MappedValue& value, std::size_t numberOfPartitions) {
        return 0;
    }

    std::size_t abcPartitioner(const std::string& key, const MappedValue& value, std::size_t numberOfPartitions) {
        switch(key[0]) {
            case 'a':
                return 0;
            case 'b':
                return 1;
            default:
                return 2;
        }
    }
}

TEST(ShufflerTest, oneMapperOneReducer) {
    //given
    MappedData mapper;
    mapper["a"] = { "aa", "ay" };
    mapper["aa"] = { "aa" };
    mapper["ay"] = { "ay" };
    mapper["zz"] = { "zz" };

    std::vector<MappedData> input = { mapper };

    std::size_t numberOfReducers = 1;
    std::vector<MappedData> output;

    //when
    Shuffler shuffler(numberOfReducers, simplePartitioner);
    shuffler.shuffle(input, output);

    //then
    ASSERT_EQ(mapper.size(), output[0].size());
    ASSERT_TRUE(mapper == output[0]);
}

TEST(ShufflerTest, mergeAndSplitOnPartitions) {
    //given
    MappedData mapper1;
    mapper1["a"] = { "ax", "az" };
    mapper1["ax"] = { "ax" };
    mapper1["az"] = { "az" };
    mapper1["b"] = { "b", "by" };
    mapper1["by"] = { "by" };

    MappedData mapper2;
    mapper2["b"] = { "bx" };
    mapper2["bx"] = { "bx" };
    mapper2["c"] = { "c", "cy" };
    mapper2["cy"] = { "cy" };

    MappedData mapper3;
    mapper3["a"] = { "a", "ay" };
    mapper3["ay"] = { "ay" };
    mapper3["b"] = { "b", "bz" };
    mapper3["bz"] = { "bz" };
    mapper3["c"] = { "c", "cx" };
    mapper3["cx"] = { "cx" };
    
    std::vector<MappedData> input = { mapper1, mapper2, mapper3 };

    std::size_t numberOfReducers = 3;
    std::vector<MappedData> output;

    //when
    Shuffler shuffler(numberOfReducers, abcPartitioner);
    shuffler.shuffle(input, output);

    //then
    auto reducer1 = output[0];
    auto reducer2 = output[1];
    auto reducer3 = output[2];
    ASSERT_EQ(4, reducer1.size());
    ASSERT_THAT(reducer1["a"], UnorderedElementsAre("a", "ax", "ay", "az"));
    ASSERT_THAT(reducer1["ax"], UnorderedElementsAre("ax"));
    ASSERT_THAT(reducer1["ay"], UnorderedElementsAre("ay"));
    ASSERT_THAT(reducer1["az"], UnorderedElementsAre("az"));
    ASSERT_EQ(4, reducer2.size());
    ASSERT_THAT(reducer2["b"], UnorderedElementsAre("b", "bx", "by", "bz"));
    ASSERT_THAT(reducer2["bx"], UnorderedElementsAre("bx"));
    ASSERT_THAT(reducer2["by"], UnorderedElementsAre("by"));
    ASSERT_THAT(reducer2["bz"], UnorderedElementsAre("bz"));
    ASSERT_EQ(3, reducer3.size());
    ASSERT_THAT(reducer3["c"], UnorderedElementsAre("c", "cx", "cy"));
    ASSERT_THAT(reducer3["cx"], UnorderedElementsAre("cx"));
    ASSERT_THAT(reducer3["cy"], UnorderedElementsAre("cy"));
}
