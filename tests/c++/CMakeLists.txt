set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

enable_language(CXX)

include_directories(${INCLUDES} ${kodidevkit_SOURCE_DIR}/include)

# add_definitions(-DTARGET_POSIX)

set(TESTSYSTEM_INCLUDES ${INCLUDES})

add_executable(cpptest main.cpp)
add_dependencies(cpptest kodidevkit)
target_link_libraries(cpptest kodidevkit)
target_include_directories(cpptest PRIVATE ${INCLUDES})
