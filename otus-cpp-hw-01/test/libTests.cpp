#define BOOST_TEST_MODULE libTests

#include "lib.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(libTests)

BOOST_AUTO_TEST_CASE(testVersion)
{
    BOOST_CHECK(Example::getVersion() > 0);
}

BOOST_AUTO_TEST_SUITE_END()