cmake_minimum_required(VERSION 2.6)
project(GTest_Scratchpad)

#
# CMake will initialize with many variables, which can be seen in
# the directory where build outputs are placed (wherever you call cmake)
# the variables are defined in CMakeCache.txt. We must modify them here
#

# add a location for CMake to look for header files
include_directories(./include)

# we have some source files that need built into objects and linked. We will build them as a library and link
add_library(num STATIC ${CMAKE_SOURCE_DIR}/src/num.cpp)

if(build_tests)
  message(STATUS "building test libraries and tests")
  add_subdirectory(deps/gtest)

#
# warning: no effort was made to make this pretty. It is a proof of concept.
#
  include_directories(${CMAKE_SOURCE_DIR}/deps/gtest/googletest/include)
  add_executable(num_tests ${CMAKE_SOURCE_DIR}/tests/num_unittests.cpp ${CMAKE_SOURCE_DIR}/deps/gtest/googletest/src/gtest_main.cc)
  target_link_libraries(num_tests gtest num)
else()
  message(STATUS "not building tests or test libraries")
endif()

# this produces the main executable, linked with the libraries produced in /src/
add_executable(main main.cpp)
target_link_libraries(main num)