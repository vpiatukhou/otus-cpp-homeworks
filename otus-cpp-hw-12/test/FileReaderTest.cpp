#include "FileReader.h"

#include "gtest/gtest.h"

#include <cstdio>
#include <fstream>
#include <string>

namespace {
    using namespace Homework;
    using namespace std::string_literals;

    /**
     * Creates and deletes test data.
     *
     * We create a file dynamically in order to guarantee that nobody accidentally changes newline characters.
     */
    class FileReaderTest : public ::testing::Test {
    protected:
        std::string tempFilepath;

        FileReaderTest() {
            tempFilepath = "temp.txt"s;
            std::ofstream testFile(tempFilepath);
            testFile << "AAAA\nBBB\nCCCCCC\nDDDD";
        }

        ~FileReaderTest() {
            std::remove(tempFilepath.c_str());
        }
    };
}

TEST_F(FileReaderTest, readInMiddleOfFile) {
    //when
    FileReader reader(tempFilepath, 5, 16);

    //then
    std::string line;
    reader.readLine(line);
    ASSERT_EQ("BBB", line);
    ASSERT_TRUE(reader.hasNext());

    reader.readLine(line);
    ASSERT_EQ("CCCCCC", line);
    ASSERT_FALSE(reader.hasNext());
}

TEST_F(FileReaderTest, readUntilEndOfFile) {
    //when
    FileReader reader(tempFilepath, 5, 20);

    //then
    std::string line;
    reader.readLine(line);
    ASSERT_EQ("BBB", line);
    ASSERT_TRUE(reader.hasNext());

    reader.readLine(line);
    ASSERT_EQ("CCCCCC", line);
    ASSERT_TRUE(reader.hasNext());

    reader.readLine(line);
    ASSERT_EQ("DDDD", line);
    ASSERT_FALSE(reader.hasNext());
}
