cmake_minimum_required(VERSION 3.15)
project(plugin CXX)

find_package(Poco CONFIG REQUIRED)
find_package(plugininterface CONFIG REQUIRED)

add_library(plugin SHARED src/PluginFactory.cpp)

target_link_libraries(plugin PRIVATE Poco::Poco plugininterface::plugininterface)

install(TARGETS plugin)
