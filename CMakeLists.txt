cmake_minimum_required(VERSION 3.7)
project(kodidevkit CXX)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

find_package(Threads REQUIRED)
find_package(Kodi REQUIRED)

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)

# Set CMAKE_INSTALL_LIBDIR if not defined
include(GNUInstallDirs)

# Older cmake might not pick CMAKE_INSTALL_LIBDIR right
if(CMAKE_INSTALL_LIBDIR)
  set(LIB_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}" CACHE PATH "Installation path for libraries")
else()
  set(LIB_INSTALL_DIR "lib" CACHE PATH "Installation path for libraries")
endif()

# By default, build shared object libraries on linux
# if (UNIX AND NOT APPLE)
#   if (NOT DEFINED BUILD_SHARED_LIBS)
#     set(BUILD_SHARED_LIBS ON)
#   endif()
# endif()
#if (NOT WIN32)
#  list(APPEND CMAKE_C_FLAGS "-fPIC")
#  list(APPEND CMAKE_CXX_FLAGS "-fPIC")
#endif()

# Appends the cmake/modules path to MAKE_MODULE_PATH variable.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

message(INFO " - kodidevkit Version ${VERSION}")
message(INFO " - cmake Version ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

# this is the library version, independant of git revision
set(kodidevkit_VERSION_MAJOR ${VERSION_MAJOR})
set(kodidevkit_VERSION_MINOR ${VERSION_MINOR})
set(kodidevkit_VERSION_PATCH ${VERSION_PATCH})
set(kodidevkit_VERSION_STRING ${kodidevkit_VERSION_MAJOR}.${kodidevkit_VERSION_MINOR}.${kodidevkit_VERSION_PATCH})
set(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(CMAKE_SWIG_FLAGS "")

option(BUILDDOC "Build all doc." OFF)
option(BUILDSWIG "Build swig modules." ON)
option(BUILDSWIGPYTHON "Build swig python modules." ON)
option(BUILDSWIGNODE "Build swig node modules." ON)
option(BUILDSWIGJAVA "Build Java API." ON)
option(BUILDSWIGLUA "Build Lua API." ON)
option(BUILDARCH "Override architecture to build for - override" OFF)
option(BUILDPYTHON3 "Use python3 for building/installing/testing" OFF)
option(ENABLEEXAMPLES "Enable building of examples" OFF)
option(BUILDTESTS "Override the addition of tests" ON)
option(USEPYTHON3TESTS "Force tests to run with python3" OFF)

set(BUILDARCH "" CACHE STRING "Override architecture to build for")

if(NOT BUILDSWIG)
  set(BUILDSWIGPYTHON OFF)
  set(BUILDSWIGNODE OFF)
  set(BUILDSWIGJAVA OFF)
  set(BUILDSWIGLUA OFF)
endif()

if(NOT BUILDARCH)
  include(TargetArch)
  target_architecture(DETECTED_ARCH)
  message(STATUS "INFO - Target arch is ${DETECTED_ARCH}")
else()
  set(DETECTED_ARCH ${BUILDARCH})
  message(STATUS "INFO - Override arch is ${DETECTED_ARCH}")
endif()

set (kodidevkit_LIB_INCLUDE_DIRS
  ${PROJECT_SOURCE_DIR}/include
)

if(BUILDSWIGPYTHON OR BUILDTESTS)
  include(cmake/modules/OpenCVDetectPython.cmake)
endif()

if(BUILDDOC)
  # add a target to generate API documentation with Doxygen
  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    if(BUILDSWIGJAVA)
      configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.java.in ${CMAKE_CURRENT_BINARY_DIR}/src/java/Doxyfile @ONLY)
    endif()
    add_custom_target(doc
      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
  endif()
endif()

if(IPK)
  # Get target package arch from Yocto ADT sysroot if set or host OS, mapping to Ubuntu name if necessary
  if(DEFINED ENV{OECORE_TARGET_SYSROOT})
    GET_FILENAME_COMPONENT (DETECTED_SYSROOT $ENV{OECORE_TARGET_SYSROOT} NAME)
    string (REGEX REPLACE "-poky-linux" "" TARGET_ARCH "${DETECTED_SYSROOT}")
  else()
    # debian uses amd64 to denote x86_64
    if(DETECTED_ARCH STREQUAL "x86_64")
      set(TARGET_ARCH "amd64")
    else()
      set(TARGET_ARCH ${DETECTED_ARCH})
    endif()
  endif()

  message(STATUS "INFO - Package arch is ${TARGET_ARCH}")
  set(CPACK_GENERATOR "DEB" "TGZ")
  set(OPKG_ARCH ${TARGET_ARCH})
  set(CPACK_BINARY_DIR ${CMAKE_BINARY_DIR})
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Team Kodi") #required
  set(kodidevkit_PACKAGE_ON_TAG ".")
  if ("${VERSION_COMMIT}" STREQUAL "")
    set(kodidevkit_PACKAGE_ON_TAG "")
  endif()
  set(CPACK_PACKAGE_VERSION
      "${kodidevkit_VERSION_MAJOR}.${kodidevkit_VERSION_MINOR}.${kodidevkit_VERSION_PATCH}${kodidevkit_PACKAGE_ON_TAG}${VERSION_COMMIT}")
  set(CPACK_PACKAGE_NAME "kodidevkit")
  set(CPACK_DEBIAN_PACKAGE_SECTION "libs")
  set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${TARGET_ARCH})
  set(CPACK_SYSTEM_NAME ${TARGET_ARCH})
  set(CPACK_DEBIAN_PACKAGE_PROVIDES "kodidevkit-dev, kodidevkit-dbg, kodidevkit-doc")
  set(CPACK_DEBIAN_PACKAGE_REPLACES "${CPACK_DEBIAN_PACKAGE_PROVIDES}, libkodidevkit, libkodidevkit-dev, libkodidevkit-doc")
  set(CPACK_DEBIAN_PACKAGE_CONFLICTS ${CPACK_DEBIAN_PACKAGE_PROVIDES})
  set(WDIR "${CPACK_TOPLEVEL_DIRECTORY}/${CPACK_PACKAGE_FILE_NAME}")
  include(CPack)
endif()

if(RPM)
  message(STATUS "INFO - Enabled RPM packaging for ${DETECTED_ARCH}")
  set(CMAKE_INSTALL_PREFIX "/usr")
  set(CPACK_PACKAGE_VERSION ${VERSION})
  set(CPACK_GENERATOR "RPM")
  set(CPACK_PACKAGE_NAME "libkodidevkit${kodidevkit_VERSION_MAJOR}")
  set(CPACK_PACKAGE_RELEASE 1)
  set(CPACK_PACKAGE_VERSION
      "${kodidevkit_VERSION_MAJOR}.${kodidevkit_VERSION_MINOR}.${kodidevkit_VERSION_PATCH}${kodidevkit_PACKAGE_ON_TAG}${VERSION_COMMIT}")
  set(CPACK_PACKAGE_CONTACT "Team Kodi")
  set(CPACK_PACKAGE_VENDOR "Team Kodi")
  set(CPACK_RPM_PACKAGE_PROVIDES "${CPACK_PACKAGE_NAME}-devel")
  # Get distro tag (e.g. 'fc20') by parsing output of rpm --showrc
  EXECUTE_PROCESS(
    COMMAND rpm --showrc
    COMMAND grep -w dist
    COMMAND sed -e "s/\\t./ /"
    COMMAND awk "{printf \"%s\", \$NF}"
    OUTPUT_VARIABLE DIST_TAG
  )
  set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${DIST_TAG}.${DETECTED_ARCH}")
  include(CPack)
endif()

add_subdirectory(src)
if(ENABLEEXAMPLES)
  add_subdirectory(examples)
endif()

if (BUILDTESTS AND PYTHON_DEFAULT_EXECUTABLE)
  enable_testing()
  add_subdirectory(tests)
endif()
