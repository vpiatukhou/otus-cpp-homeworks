#include "ShortestPrefixFinder.h"

#include "gmock/gmock.h"

namespace {
    using namespace Homework;
    using ::testing::UnorderedElementsAre;
}

TEST(ShortestPrefixFinderTest, mapPositive) {
    //given
    MappedData output;

    //when
    map("aaxx", output);
    map("aayy", output);
    map("aayzz", output);

    //then
    ASSERT_EQ(8, output.size());
    ASSERT_THAT(output["a"], UnorderedElementsAre("aaxx", "aayy", "aayzz"));
    ASSERT_THAT(output["aa"], UnorderedElementsAre("aaxx", "aayy", "aayzz"));
    ASSERT_THAT(output["aax"], UnorderedElementsAre("aaxx"));
    ASSERT_THAT(output["aaxx"], UnorderedElementsAre("aaxx"));
    ASSERT_THAT(output["aay"], UnorderedElementsAre("aayy", "aayzz"));
    ASSERT_THAT(output["aayy"], UnorderedElementsAre("aayy"));
    ASSERT_THAT(output["aayz"], UnorderedElementsAre("aayzz"));
    ASSERT_THAT(output["aayzz"], UnorderedElementsAre("aayzz"));
}

TEST(ShortestPrefixFinderTest, reducePositive) {
    //given
    ReduceOutput output;
    MappedValue value1 = {"aaxx", "aayy", "aayzz"};
    MappedValue value2 = {"aaxx"};
    MappedValue value3 = {"aayy", "aayzz"};
    MappedValue value4 = {"aayy"};
    MappedValue value5 = {"aayzz"};
    
    //when
    reduce("a", value1, output);
    reduce("aa", value1, output);
    reduce("aax", value2, output);
    reduce("aaxx", value2, output);
    reduce("aay", value3, output);
    reduce("aayy", value4, output);
    reduce("aayz", value5, output);
    reduce("aayzz", value5, output);

    //then
    ASSERT_EQ(3, output.size());
    ASSERT_EQ("aax", output["aaxx"]);
    ASSERT_EQ("aayy", output["aayy"]);
    ASSERT_EQ("aayz", output["aayzz"]);
}
