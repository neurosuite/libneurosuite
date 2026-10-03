# Configures against an *installed* libneurosuite to check the exported CMake package.
cmake_minimum_required(VERSION 3.16)
project(neurosuite_consumer CXX)
set(CMAKE_CXX_STANDARD 17)
find_package(neurosuite 3.0 REQUIRED)
add_executable(consumer main.cpp)
target_link_libraries(consumer PRIVATE neurosuite::neurosuite)
