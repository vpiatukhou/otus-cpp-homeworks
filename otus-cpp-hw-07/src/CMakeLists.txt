add_executable(bulk_cli main.cpp)
add_library(bulk CommandProcessor.cpp BaseCommandWriter.cpp ConsoleCommandWriter.cpp FileCommandWriter.cpp)

#rename the executable to "bulk"
set_target_properties(bulk_cli PROPERTIES OUTPUT_NAME bulk)

target_link_libraries(bulk_cli PRIVATE bulk)

#BEGIN release
install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
#END