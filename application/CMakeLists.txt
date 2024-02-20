cmake_minimum_required(VERSION 3.15)
project(application CXX)

find_package(Poco CONFIG REQUIRED)
find_package(plugininterface CONFIG REQUIRED)

add_executable(application src/main.cpp)

target_link_libraries(application PRIVATE Poco::Poco plugininterface::plugininterface)

set_target_properties(application PROPERTIES INSTALL_RPATH "$ORIGIN/../lib")
install(TARGETS application DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
