cmake_minimum_required(VERSION 2.8)
project(simple-lua-wrapper)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra")

include_directories(
        ../vendor/lua
        example/src
)

file(GLOB LUA_SRCS ../vendor/lua/*.c)
file(GLOB_RECURSE SRCS ./src/*)

add_library(lua STATIC ${LUA_SRCS})
add_library(simple-lua-wrapper STATIC ${SRCS})

target_link_libraries(simple-lua-wrapper lua)
