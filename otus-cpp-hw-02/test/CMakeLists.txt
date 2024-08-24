add_executable(ip_filter_tests IpConvertorTests.cpp IpFilterTests.cpp)

set_target_properties(ip_filter_tests PROPERTIES 
    CMAKE_CXX_STANDARD 14 
    CXX_STANDARD_REQUIRED ON
)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

if (WIN32)
    # Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

target_include_directories(ip_filter_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(ip_filter_tests ip_filter GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(ip_filter_tests)

enable_testing()