cmake_minimum_required(VERSION 3.10)
project(CLEAN_PROJECT CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(flags "-std=c++17")
set(debug_flags "-O0 -g1")
set(release_flags "-O2 -DNDEBUG")
set(warnings "-Wall -Wextra -Wpedantic")

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} ${flags}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${debug_flags}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${release_flags}")

file(GLOB MY_SOURCE_FILES
  src/*.cpp
  # ${CMAKE_SOURCE_DIR}/src/**/*.cpp
  )
add_executable(main ${MY_SOURCE_FILES})

set(MY_INCLUDE_FILES ${CMAKE_SOURCE_DIR}/src/)
target_include_directories(main PUBLIC ${MY_INCLUDE_FILES})
