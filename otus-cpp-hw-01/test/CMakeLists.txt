add_executable(libTests libTests.cpp)

set_target_properties(libTests PROPERTIES 
    CMAKE_CXX_STANDARD 14 
    CXX_STANDARD_REQUIRED ON
)

find_package(Boost COMPONENTS REQUIRED unit_test_framework)
target_compile_definitions(libTests PRIVATE BOOST_TEST_DYN_LINK)
target_include_directories(libTests PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(libTests PRIVATE ${Boost_LIBRARIES} helloworld)

enable_testing()
add_test(NAME libTests COMMAND libTests)