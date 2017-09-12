set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

enable_language(CXX)

# find_package(JsonCpp REQUIRED)
find_package(MsgPack REQUIRED)
find_package(p8-platform REQUIRED)

list(APPEND DEPLIBS ${JSONCPP_LIBRARIES}
                    ${p8-platform_LIBRARIES})
list(APPEND INCLUDES ${JSONCPP_INCLUDE_DIRS}
                     ${PROJECT_SOURCE_DIR})

include_directories(${INCLUDES}
                    ${kodidevkit_SOURCE_DIR}/include
                    ${testsystem_SOURCE_DIR}/testserver)

add_definitions(-DHAS_EVENT_SERVER)

set(TESTSERVER_SOURCES main.cpp
                       addons/AddonVersion.cpp
                       addons/binary/BinaryAddon.cpp
                       addons/binary/BinaryAddonManager.cpp
                       addons/binary/intfc-shared/SharedMemory.cpp
                       addons/binary/intfc-shared/SharedMemoryPosix.cpp
                       network/Network.cpp
                       network/Socket.cpp
                       utils/JobManager.cpp
                       utils/log.cpp)

add_executable(testserver ${TESTSERVER_SOURCES})
target_link_libraries(testserver ${DEPLIBS})
target_include_directories(testserver PRIVATE ${INCLUDES})
