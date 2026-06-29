cmake_minimum_required(VERSION 3.15)
project(Arbor VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(ARBOR_BUILD_TESTS "Build tests" ON)
option(ARBOR_BUILD_BENCHMARKS "Build benchmarks" ON)
option(ARBOR_BUILD_STUB "Build RAM-only stub for Ajay" ON)

# Core library — explicit sources, add files here as you create them
add_library(arbor_core STATIC
  src/page_manager.cpp
  src/wal.cpp
  src/telemetry.cpp
)

target_include_directories(arbor_core PUBLIC include)

target_compile_options(arbor_core PRIVATE
  -Wall -Wextra -Wpedantic
  $<$<CONFIG:Debug>:-g -O0>
  $<$<CONFIG:Release>:-O3>
)

# Subdirectories
if(ARBOR_BUILD_STUB)
  add_subdirectory(stub)
endif()

if(ARBOR_BUILD_TESTS)
  enable_testing()
  add_subdirectory(third_party/googletest)
  add_subdirectory(tests)
endif()

if(ARBOR_BUILD_BENCHMARKS)
  add_subdirectory(benchmarks)
endif()
