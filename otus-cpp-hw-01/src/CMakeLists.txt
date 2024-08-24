add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)

set_target_properties(helloworld_cli helloworld PROPERTIES 
    CMAKE_CXX_STANDARD 14 
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(helloworld PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated_sources)
target_link_libraries(helloworld_cli PRIVATE helloworld)

configure_file(version.h.in ${CMAKE_CURRENT_BINARY_DIR}/generated_sources/version.h @ONLY)

#BEGIN release
install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
#END