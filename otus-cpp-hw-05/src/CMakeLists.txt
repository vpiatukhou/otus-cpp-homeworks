add_executable(editor main.cpp DocumentController.cpp ToolController.cpp DocumentManager.cpp ToolProvider.cpp DocumentExporterFactory.cpp DocumentImporterFactory.cpp)

set_target_properties(editor PROPERTIES 
    CMAKE_CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

#BEGIN release
install(TARGETS editor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
#END