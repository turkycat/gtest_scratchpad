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

message(STATUS "Are we building tests and dependent libraries?")
if(build_tests)
  message(STATUS "YES - Building test libraries and tests")

  # googletest has their own CMake files, so simply reference the directory to build the entire library
  add_subdirectory(deps/gtest)

  # our test files will reference gtest/gtest.h, so add an include directory for that.
  include_directories(${CMAKE_SOURCE_DIR}/deps/gtest/googletest/include)

  # grab a list of all source files in the test directory, store as {TESTFILES}
  file(GLOB TESTFILES test/*.cpp)

  # build all test files into a single executable, this will include our testmain.cpp
  add_executable(runtests ${TESTFILES})

  #finally, link runtests executable with the gtest library and our custom library.
  target_link_libraries(runtests gtest num)

  #
  # Integration test target
  #
  include_directories(${CMAKE_SOURCE_DIR}/deps/gtest/googlemock/include)
  include_directories(${CMAKE_SOURCE_DIR}/test/integration)
  add_executable(integration test/integration/mapreduce_mocknum_integration.cpp)
  target_link_libraries(integration gtest gmock num)

else()
  message(STATUS "NO - not building tests or test libraries")
endif()

# this produces the main executable, linked with the libraries produced in /src/
add_executable(main main.cpp)
target_link_libraries(main num)