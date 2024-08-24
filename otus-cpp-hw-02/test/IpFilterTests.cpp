#include "IpFilter.h"
#include <gtest/gtest.h>

namespace HomeworkTest {
    
    void verifyIpAddresses(const std::vector<Homework::IpAddress>& expected, const std::vector<Homework::IpAddress>& actual) {
        EXPECT_EQ(expected.size(), actual.size());
        for (size_t i = 0; i < expected.size(); ++i) {
            EXPECT_EQ(expected[i], actual[i]);
        }
    }
}

TEST(FilterIpTest, filterByFirstPart) {
    //given
    std::vector<Homework::IpAddress> ipAddresses = { 
        {1, 1, 1, 1},
        {1, 2, 2, 2},
        {2, 1, 2, 2},
        {2, 2, 1, 2},
        {2, 2, 2, 1},
        {10, 2, 3, 4},
        {100, 2, 3, 4}
    };

    //when
    auto actual = Homework::filter(ipAddresses, 1);

    //then
    std::vector<Homework::IpAddress> expected = { 
        {1, 1, 1, 1},
        {1, 2, 2, 2}
    };

    HomeworkTest::verifyIpAddresses(expected, actual);
}

TEST(FilterIpTest, filterByTwoParts) {
    //given
    std::vector<Homework::IpAddress> ipAddresses = { 
        {46, 70, 2, 2},
        {46, 70, 2, 3},
        {2, 70, 2, 2},
        {46, 2, 2, 2},
        {2, 46, 70, 2}
    };

    //when
    auto actual = Homework::filter(ipAddresses, 46, 70);

    //then
    std::vector<Homework::IpAddress> expected = { 
        {46, 70, 2, 2},
        {46, 70, 2, 3}
    };

    HomeworkTest::verifyIpAddresses(expected, actual);
}

TEST(FilterIpTest, filterAny) {
    //given
    std::vector<Homework::IpAddress> ipAddresses = { 
        {46, 2, 2, 2},
        {2, 46, 2, 2},
        {2, 2, 46, 2},
        {2, 2, 2, 46},
        {2, 2, 2, 2}
    };

    //when
    auto actual = Homework::filterAny(ipAddresses, 46);

    //then
    std::vector<Homework::IpAddress> expected = { 
        {46, 2, 2, 2},
        {2, 46, 2, 2},
        {2, 2, 46, 2},
        {2, 2, 2, 46}
    };

    HomeworkTest::verifyIpAddresses(expected, actual);
}

TEST(FilterIpTest, filterIpAddressesSortingOnly) {
    //the given IP addresses do NOT match any of filter mask. This test verifies sorting only.
    std::vector<Homework::IpAddress> ipAddresses = { 
        {2, 2, 2, 40},
        {2, 2, 30, 2},
        {2, 20, 2, 2},
        {10, 2, 2, 2},
        {10, 2, 2, 2}
    };

    //when
    auto actual = Homework::filterIpAddresses(ipAddresses);

    //then
    std::vector<Homework::IpAddress> expected = { 
        {10, 2, 2, 2},
        {10, 2, 2, 2},
        {2, 20, 2, 2},
        {2, 2, 30, 2},
        {2, 2, 2, 40},
    };

    HomeworkTest::verifyIpAddresses(expected, actual);
}

/// @brief tests that sorted and filtered IP addresses are combined together
TEST(FilterIpTest, filterIpAddressesCombinedResult) {
    std::vector<Homework::IpAddress> ipAddresses = { 
        //the following IPs don't match any filter mask. They will be sorted only.
        {2, 2, 2, 40},
        {40, 2, 2, 2},
        //the following IPs match 1.x.x.x mask
        {1, 2, 2, 2},
        {1, 3, 3, 3},
        //the following IPs match 46.70.x.x AND 46.x.x.x masks. So every IP will be added twice to the result list.
        {46, 70, 2, 2},
        {46, 70, 2, 3},
        //the following IPs match x.46.x.x, x.x.46.x and x.x.x.46 masks
        {2, 46, 2, 2},
        {2, 2, 46, 2},
        {2, 2, 2, 46}
    };

    //when
    auto actual = Homework::filterIpAddresses(ipAddresses);

    //then
    std::vector<Homework::IpAddress> expected = { 
        //sorted IP addresses
        {46, 70, 2, 3},
        {46, 70, 2, 2},
        {40, 2, 2, 2},
        {2, 46, 2, 2},
        {2, 2, 46, 2},
        {2, 2, 2, 46},
        {2, 2, 2, 40},
        {1, 3, 3, 3},
        {1, 2, 2, 2},
        //filtered by 1.x.x.x
        {1, 3, 3, 3},
        {1, 2, 2, 2},
        //filtered by 46.70.x.x
        {46, 70, 2, 3},
        {46, 70, 2, 2},
        //filtered by 46.x.x.x, x.46.x.x, x.x.46.x and x.x.x.46
        {46, 70, 2, 3},
        {46, 70, 2, 2},
        {2, 46, 2, 2},
        {2, 2, 46, 2},
        {2, 2, 2, 46}
    };

    HomeworkTest::verifyIpAddresses(expected, actual);
}