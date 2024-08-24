add_executable(allocator_tests MyAllocatorTests.cpp LinkedListTests.cpp LinkedListWithMyAllocatorTests.cpp)

set_target_properties(allocator_tests PROPERTIES 
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

target_include_directories(allocator_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(allocator_tests GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(allocator_tests)

enable_testing()