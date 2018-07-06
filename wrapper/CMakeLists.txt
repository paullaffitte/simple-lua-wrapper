##
## MIT License
##
## Copyright (c) 2018 Paul Laffitte
##
## Permission is hereby granted, free of charge, to any person obtaining a copy
## of this software and associated documentation files (the "Software"), to deal
## in the Software without restriction, including without limitation the rights
## to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
## copies of the Software, and to permit persons to whom the Software is
## furnished to do so, subject to the following conditions:
##
## The above copyright notice and this permission notice shall be included in all
## copies or substantial portions of the Software.
##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
## AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
## OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
## SOFTWARE.
##

cmake_minimum_required(VERSION 3.0)
project(SimpleLuaWrapper)

# SIMPLE LUA WRAPPER ##################
file(GLOB_RECURSE SRCS ./src/*)
add_library(SimpleLuaWrapper STATIC ${SRCS})
#######################################

set_property(TARGET SimpleLuaWrapper PROPERTY CXX_STANDARD 14)

#target_include_directories(SimpleLuaWrapper PUBLIC ../vendor/lua)
target_include_directories(SimpleLuaWrapper PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/example/src>
    $<INSTALL_INTERFACE:include/slw>) # TODO add PUBLIC include and make src PRIVATE

target_compile_options(SimpleLuaWrapper PRIVATE -W -Wall -Wextra)

add_subdirectory(vendor/modern-cmake-lua)
#target_link_libraries(SimpleLuaWrapper PUBLIC lua)
target_link_libraries(SimpleLuaWrapper PUBLIC cmake_lua)

install(EXPORT SimpleLuaWrapperTargets
    FILE SimpleLuaWrapperTargets.cmake
    NAMESPACE SimpleLuaWrapper::
    DESTINATION lib/cmake/SimpleLuaWrapper
    )

install(TARGETS SimpleLuaWrapper EXPORT SimpleLuaWrapperTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )
