set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(mapreduce_test FileReaderTest.cpp
                              ShortestPrefixFinderTest.cpp
                              ShufflerTest.cpp
                              SplitterTest.cpp)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)

target_include_directories(mapreduce_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(mapreduce_test mapreduce GTest::gtest GTest::gtest_main GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(mapreduce_test)
