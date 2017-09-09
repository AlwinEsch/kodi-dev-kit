find_package(Lua REQUIRED)

set_source_files_properties (kodidevkitlua.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties (kodidevkitlua.i PROPERTIES SWIG_FLAGS "-I${CMAKE_BINARY_DIR}/src")

message ("LUA attempting to build!")

if (CMAKE_VERSION VERSION_LESS "3.8")
  swig_add_module (kodi-lua lua kodidevkitlua.i)
else ()
  swig_add_library (kodi-lua LANGUAGE lua SOURCES kodidevkitlua.i)
endif ()
swig_link_libraries (kodi-lua ${LUA_LIBRARIES} kodidevkit)

target_include_directories(${SWIG_MODULE_kodi-lua_REAL_NAME}
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/../.."
  "${LUA_INCLUDE_DIR}"
)
