#include "Splitter.h"

#include "gtest/gtest.h"

#include <string>

namespace {
    using namespace Homework;
    using namespace std::string_literals;

    /**
     * Creates and deletes test data.
     *
     * We create a file dynamically in order to guarantee that nobody accidentally changes newline characters.
     */
    class SplitterTest : public ::testing::Test {
    protected:
        std::string tempFilepath;

        void createTestData(const std::string& fileContent) {
            tempFilepath = "temp.txt"s;
            std::ofstream testFile(tempFilepath);
            testFile << fileContent;
        }

        ~SplitterTest() {
            std::remove(tempFilepath.c_str());
        }
    };
}

TEST_F(SplitterTest, singleChar) {
    //given
    createTestData("a");

    Splitter splitter(tempFilepath, 1);

    //when
    auto result = splitter.splitInputData();

    //then
    ASSERT_EQ(1, result.size());
    ASSERT_EQ(1, result[0]->getEndPosition());
}

TEST_F(SplitterTest, moreMappersThanData) {
    //given
    createTestData("a");

    Splitter splitter(tempFilepath, 2); //it is not possible to split data for two mappers

    //when
    auto result = splitter.splitInputData();

    //then
    ASSERT_EQ(1, result.size());
    ASSERT_EQ(1, result[0]->getEndPosition());
}

TEST_F(SplitterTest, allLinesEqual) {
    //given
    createTestData("AAA\nBBB\nCCC\nXDD");

    Splitter splitter(tempFilepath, 2);

    //when
    auto result = splitter.splitInputData();

    //then
    ASSERT_EQ(2, result.size());
    ASSERT_EQ(12, result[0]->getEndPosition()); //The first section is bigger. It is not a defect, please see Splitter::splitInputData()
    ASSERT_EQ(15, result[1]->getEndPosition());
}

TEST_F(SplitterTest, firstLineBigger) {
    //given
    createTestData("AAAAA\nXB");

    Splitter splitter(tempFilepath, 2);

    //when
    auto result = splitter.splitInputData();

    //then
    ASSERT_EQ(2, result.size());
    ASSERT_EQ(6, result[0]->getEndPosition());
    ASSERT_EQ(8, result[1]->getEndPosition());
}

TEST_F(SplitterTest, secondLineBigger) {
    //given
    createTestData("AA\nBBBBB");

    Splitter splitter(tempFilepath, 2); //the number of mappers is 2 but it is impossible to split the data

    //when
    auto result = splitter.splitInputData();

    //then
    ASSERT_EQ(1, result.size());
    ASSERT_EQ(8, result[0]->getEndPosition());
}

TEST_F(SplitterTest, complexPartitions) {
    //given
    createTestData("AAAA\nBBBBBB\nCCC\nDDDD\nEEEEEE\nXFFFFF\nGGGGGGGGG\nHHHH\nIIIII\nX\nKKKKKKKK\nLLLLL");

    Splitter splitter(tempFilepath, 3);

    //when
    auto result = splitter.splitInputData();

    //then
    ASSERT_EQ(3, result.size());
    ASSERT_EQ(28, result[0]->getEndPosition());
    ASSERT_EQ(56, result[1]->getEndPosition());
    ASSERT_EQ(72, result[2]->getEndPosition());
}
