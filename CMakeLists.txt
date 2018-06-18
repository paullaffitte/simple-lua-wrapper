cmake_minimum_required(VERSION 2.8)
project(simple-lua-wrapper-example)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra")

add_subdirectory(wrapper)

include_directories(
        ./src
        ./example/inc
        ./vendor/lua
)

file(GLOB_RECURSE SRCS ./example/src/*)

add_executable(simple-lua-wrapper-example ${SRCS})
target_link_libraries(simple-lua-wrapper-example simple-lua-wrapper)

