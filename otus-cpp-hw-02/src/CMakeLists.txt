add_executable(ip_filter_cli main.cpp)
add_library(ip_filter IpFilter.cpp IpConvertor.cpp)

set_target_properties(ip_filter_cli ip_filter PROPERTIES 
    CMAKE_CXX_STANDARD 14 
    CXX_STANDARD_REQUIRED ON
)

#rename the executable to "ip_filter"
set_target_properties(ip_filter_cli PROPERTIES OUTPUT_NAME ip_filter)

target_link_libraries(ip_filter_cli PRIVATE ip_filter)

#BEGIN release
install(TARGETS ip_filter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
#END