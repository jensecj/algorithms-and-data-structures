cmake_minimum_required(VERSION 3.2)
project(algorithms-and-data-structures CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(libs/googletest)
add_subdirectory(libs/benchmark)

set(flags "-std=c++11")
set(debug_flags "-O0 -g1")
set(release_flags "-O2 -DNDEBUG")
set(warnings "-Wall -Wextra -Wpedantic -Werror")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} ${flags}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${debug_flags}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${release_flags}")

set(DADS_INCLUDE_FILES
  ${CMAKE_SOURCE_DIR}/src/algorithms/
  ${CMAKE_SOURCE_DIR}/src/data-structures/)
file(GLOB DADS_SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/src/algorithms/**/*.cpp
  ${CMAKE_SOURCE_DIR}/src/data-structures/**/*.cpp)

add_library(dads ${DADS_SOURCE_FILES})
target_include_directories(dads PUBLIC ${DADS_INCLUDE_FILES})

file(GLOB TEST_SOURCES
  ${CMAKE_SOURCE_DIR}/tests/algorithms/*.cpp
  ${CMAKE_SOURCE_DIR}/tests/data-structures/*.cpp)
add_executable(unit-tests ${TEST_SOURCES})
target_link_libraries(unit-tests dads gtest_main)

file(GLOB BENCHMARK_SOURCES
  ${CMAKE_SOURCE_DIR}/benchmarks/algorithms/*.cpp
  ${CMAKE_SOURCE_DIR}/benchmarks/data-structures/*.cpp)
add_executable(bench-tests ${BENCHMARK_SOURCES})
target_link_libraries(bench-tests dads benchmark)
