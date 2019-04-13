cmake_minimum_required(VERSION 2.6)
project(GTest_Scratchpad)

#
# CMake will initialize with many variables, which can be seen in
# the directory where build outputs are placed (wherever you call cmake)
# the variables are defined in CMakeCache.txt. We must modify them here
#

# add a location for CMake to look for header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# we have some source files that need built into objects and linked. We will build them as a library and link
add_library(num STATIC ${CMAKE_SOURCE_DIR}/src/num.cpp)

# this produces the main executable, linked with the libraries produced in /src/
add_executable(main main.cpp)
target_link_libraries(main num)