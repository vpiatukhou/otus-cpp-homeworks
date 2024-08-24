add_executable(bulk_test CommandProcessorTest.cpp)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)

target_include_directories(bulk_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(bulk_test bulk GTest::gtest GTest::gtest_main GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(bulk_test)

enable_testing()