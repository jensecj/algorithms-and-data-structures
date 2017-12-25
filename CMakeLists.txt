cmake_minimum_required(VERSION 3.10)
project(algorithms-and-data-structures CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_DADS_TESTS "Build the dads tests" ON)
option(BUILD_DADS_BENCHMARKS "Build the dads benchmarks" OFF)

if(BUILD_DADS_TESTS)
  set(BUILD_GMOCK OFF CACHE BOOL "do not build gmock")
  set(BUILD_GTEST ON CACHE BOOL "we only need gtest")
  add_subdirectory(libs/googletest)
endif()

if(BUILD_DADS_BENCHMARKS)
  set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "disable building the benchmark libs tests")
  add_subdirectory(libs/benchmark)
endif()

set(flags "-std=c++17")
set(debug_flags "-O0 -g1")
set(release_flags "-O2 -DNDEBUG")
set(warnings "-Wall -Wextra -Wpedantic")

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} ${flags}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${debug_flags}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${release_flags}")

set(DADS_INCLUDE_FILES ${CMAKE_SOURCE_DIR}/src/)

add_library(dads INTERFACE)
target_include_directories(dads INTERFACE ${DADS_INCLUDE_FILES})

if(BUILD_DADS_TESTS)
  file(GLOB TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/tests/algorithms/*.cpp
    ${CMAKE_SOURCE_DIR}/tests/data-structures/*.cpp)
  add_executable(unit-tests ${TEST_SOURCES})
  target_link_libraries(unit-tests dads gtest_main)
endif()

if(BUILD_DADS_BENCHMARKS)
  file(GLOB BENCHMARK_SOURCES
    ${CMAKE_SOURCE_DIR}/benchmarks/algorithms/*.cpp
    ${CMAKE_SOURCE_DIR}/benchmarks/data-structures/*.cpp)
  add_executable(bench-tests ${BENCHMARK_SOURCES})
  target_link_libraries(bench-tests dads benchmark)
endif()
