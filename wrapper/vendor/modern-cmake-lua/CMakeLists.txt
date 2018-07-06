cmake_minimum_required (VERSION 3.9 FATAL_ERROR)
project (cmake_lua VERSION 0.0 LANGUAGES C)

set(lua_src
  lua-5.3.4/src/lapi.c
  lua-5.3.4/src/lauxlib.c
  lua-5.3.4/src/lbaselib.c
  lua-5.3.4/src/lbitlib.c
  lua-5.3.4/src/lcode.c
  lua-5.3.4/src/lcorolib.c
  lua-5.3.4/src/lctype.c
  lua-5.3.4/src/ldblib.c
  lua-5.3.4/src/ldebug.c
  lua-5.3.4/src/ldo.c
  lua-5.3.4/src/ldump.c
  lua-5.3.4/src/lfunc.c
  lua-5.3.4/src/lgc.c
  lua-5.3.4/src/linit.c
  lua-5.3.4/src/liolib.c
  lua-5.3.4/src/llex.c
  lua-5.3.4/src/lmathlib.c
  lua-5.3.4/src/lmem.c
  lua-5.3.4/src/loadlib.c
  lua-5.3.4/src/lobject.c
  lua-5.3.4/src/lopcodes.c
  lua-5.3.4/src/loslib.c
  lua-5.3.4/src/lparser.c
  lua-5.3.4/src/lstate.c
  lua-5.3.4/src/lstring.c
  lua-5.3.4/src/lstrlib.c
  lua-5.3.4/src/ltable.c
  lua-5.3.4/src/ltablib.c
  lua-5.3.4/src/ltm.c
  lua-5.3.4/src/lua.c
  lua-5.3.4/src/luac.c
  lua-5.3.4/src/lundump.c
  lua-5.3.4/src/lutf8lib.c
  lua-5.3.4/src/lvm.c
  lua-5.3.4/src/lzio.c
)

set(LUA_TAR "lua-5.3.4.tar.gz")
add_custom_command(OUTPUT ${lua_src}
    COMMAND /home/onehandedpenguin/dev/personal_projects/tek2/simple-lua-wrapper/wrapper/vendor/modern-cmake-lua/download
)

set_source_files_properties(${lua_src} PROPERTIES LANGUAGE CXX)

add_library(cmake_lua STATIC ${lua_src})
add_library(cmake_lua::cmake_lua ALIAS cmake_lua)

target_compile_definitions(cmake_lua PRIVATE LUA_USE_POSIX)

target_include_directories(cmake_lua PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/lua-5.3.4/src>)
target_link_libraries(cmake_lua PUBLIC dl)

install(EXPORT cmake_luaTargets
        FILE cmake_luaTargets.cmake
        NAMESPACE cmake_lua::
        DESTINATION lib/cmake/cmake_lua
        )

install(TARGETS cmake_lua EXPORT cmake_luaTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )
