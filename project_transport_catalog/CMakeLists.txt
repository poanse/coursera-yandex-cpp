cmake_minimum_required(VERSION 2.8.9)
project (brown_final_p1)

include_directories(include)
file(GLOB SOURCES "./src/*.cpp")

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror -Wdelete-non-virtual-dtor -ggdb -std=c++17")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(brown_final ${SOURCES})
