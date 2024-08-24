#include "IpAddressType.h"
#include "IpConvertor.h"
#include <gtest/gtest.h>

namespace HomeworkTest {
    void testIpAddressPositive(const std::string& ipAddress, const Homework::IpAddress& expected) {
        auto actual = Homework::convertStringToIpAddress(ipAddress);

        for (size_t i = 0; i < 4; ++i) {
            EXPECT_EQ(expected[i], actual[i]);
        }
    }

    void testIpAddressParsingException(const std::string& ipAddress) {
        EXPECT_THROW(Homework::convertStringToIpAddress(ipAddress), Homework::IpAddressParsingException);
    }
}

TEST(IpConvertorTest, convertStringToIpAddressZeroes) {
    Homework::IpAddress expected = {0, 0, 0, 0};
    HomeworkTest::testIpAddressPositive("0.0.0.0", expected);
}

TEST(IpConvertorTest, convertStringToIpAddressMax) {
    Homework::IpAddress expected = {255, 255, 255, 255};
    HomeworkTest::testIpAddressPositive("255.255.255.255", expected);
}

TEST(IpConvertorTest, convertStringToIpAddressDifferentPartSizes) {
    Homework::IpAddress expected = {100, 20, 1, 255};
    HomeworkTest::testIpAddressPositive("100.20.1.255", expected);
}

TEST(IpConvertorTest, convertStringToIpAddressNotNumber) {
    HomeworkTest::testIpAddressParsingException("1.a.1.1");
}

TEST(IpConvertorTest, convertStringToIpAddressNotInteger) {
    HomeworkTest::testIpAddressParsingException("1.2,5.1.1");
}

TEST(IpConvertorTest, convertStringToIpAddressOutOfRange) {
    HomeworkTest::testIpAddressParsingException("1.256.1.1");
}

TEST(IpConvertorTest, convertStringToIpAddressNegative) {
    HomeworkTest::testIpAddressParsingException("1.-1.1.1");
}

TEST(IpConvertorTest, convertStringToIpAddressTooLittleDelimiters) {
    HomeworkTest::testIpAddressParsingException("1.1.1");
}

TEST(IpConvertorTest, convertStringToIpAddressTooManyDelimiters) {
    HomeworkTest::testIpAddressParsingException("1.1.1.1.1");
}

TEST(IpConvertorTest, convertStringToIpAddressStartsWithDelimiter) {
    HomeworkTest::testIpAddressParsingException(".1.1.1");
}

TEST(IpConvertorTest, convertStringToIpAddressEndsWithDelimiter) {
    HomeworkTest::testIpAddressParsingException("1.1.1.");
}

TEST(IpConvertorTest, convertStringToIpAddressValueIsMissed) {
    HomeworkTest::testIpAddressParsingException("1..1.1");
}
