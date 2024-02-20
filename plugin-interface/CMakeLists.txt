cmake_minimum_required(VERSION 3.25)
project(plugininterface CXX)

find_package(Poco CONFIG REQUIRED)

add_library(plugininterface INTERFACE)
add_library(plugininterface::plugininterface ALIAS plugininterface)

target_include_directories(plugininterface
    INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_sources(plugininterface INTERFACE FILE_SET HEADERS BASE_DIRS include)
target_sources(plugininterface INTERFACE FILE_SET HEADERS FILES include/IPluginFactory.h include/PluginFactory.h)

target_link_libraries(plugininterface INTERFACE Poco::Poco)

install(TARGETS plugininterface
    FILE_SET HEADERS DESTINATION include)
