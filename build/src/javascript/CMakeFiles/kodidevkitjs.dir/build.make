# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alwin/Development/kodi-dev-kit

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alwin/Development/kodi-dev-kit/build

# Include any dependencies generated for this target.
include src/javascript/CMakeFiles/kodidevkitjs.dir/depend.make

# Include the progress variables for this target.
include src/javascript/CMakeFiles/kodidevkitjs.dir/progress.make

# Include the compile flags for this target's objects.
include src/javascript/CMakeFiles/kodidevkitjs.dir/flags.make

src/javascript/kodidevkitjsJAVASCRIPT_wrap.cxx: ../src/javascript/kodidevkitjs.i
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/alwin/Development/kodi-dev-kit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Swig source"
	cd /home/alwin/Development/kodi-dev-kit/build/src/javascript && /usr/bin/cmake -E make_directory /home/alwin/Development/kodi-dev-kit/build/src/javascript
	cd /home/alwin/Development/kodi-dev-kit/build/src/javascript && /usr/bin/swig3.0 -javascript -node -I/home/alwin/Development/kodi-dev-kit/build/src -DV8_VERSION=0x045103 -outdir /home/alwin/Development/kodi-dev-kit/build/src/javascript -c++ -I/home/alwin/Development/kodi-dev-kit/include -I/usr/include/nodejs/src -I/usr/include/nodejs/deps/v8/include -I/usr/include/nodejs/deps/uv/include -I/home/alwin/Development/kodi-dev-kit/src/javascript/.. -o /home/alwin/Development/kodi-dev-kit/build/src/javascript/kodidevkitjsJAVASCRIPT_wrap.cxx /home/alwin/Development/kodi-dev-kit/src/javascript/kodidevkitjs.i

src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o: src/javascript/CMakeFiles/kodidevkitjs.dir/flags.make
src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o: src/javascript/kodidevkitjsJAVASCRIPT_wrap.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alwin/Development/kodi-dev-kit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o"
	cd /home/alwin/Development/kodi-dev-kit/build/src/javascript && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o -c /home/alwin/Development/kodi-dev-kit/build/src/javascript/kodidevkitjsJAVASCRIPT_wrap.cxx

src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.i"
	cd /home/alwin/Development/kodi-dev-kit/build/src/javascript && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alwin/Development/kodi-dev-kit/build/src/javascript/kodidevkitjsJAVASCRIPT_wrap.cxx > CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.i

src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.s"
	cd /home/alwin/Development/kodi-dev-kit/build/src/javascript && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alwin/Development/kodi-dev-kit/build/src/javascript/kodidevkitjsJAVASCRIPT_wrap.cxx -o CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.s

src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o.requires:

.PHONY : src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o.requires

src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o.provides: src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o.requires
	$(MAKE) -f src/javascript/CMakeFiles/kodidevkitjs.dir/build.make src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o.provides.build
.PHONY : src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o.provides

src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o.provides.build: src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o


# Object files for target kodidevkitjs
kodidevkitjs_OBJECTS = \
"CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o"

# External object files for target kodidevkitjs
kodidevkitjs_EXTERNAL_OBJECTS =

src/javascript/kodidevkit.node: src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o
src/javascript/kodidevkit.node: src/javascript/CMakeFiles/kodidevkitjs.dir/build.make
src/javascript/kodidevkit.node: src/libkodidevkit.a
src/javascript/kodidevkit.node: src/javascript/CMakeFiles/kodidevkitjs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alwin/Development/kodi-dev-kit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared module kodidevkit.node"
	cd /home/alwin/Development/kodi-dev-kit/build/src/javascript && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kodidevkitjs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/javascript/CMakeFiles/kodidevkitjs.dir/build: src/javascript/kodidevkit.node

.PHONY : src/javascript/CMakeFiles/kodidevkitjs.dir/build

src/javascript/CMakeFiles/kodidevkitjs.dir/requires: src/javascript/CMakeFiles/kodidevkitjs.dir/kodidevkitjsJAVASCRIPT_wrap.cxx.o.requires

.PHONY : src/javascript/CMakeFiles/kodidevkitjs.dir/requires

src/javascript/CMakeFiles/kodidevkitjs.dir/clean:
	cd /home/alwin/Development/kodi-dev-kit/build/src/javascript && $(CMAKE_COMMAND) -P CMakeFiles/kodidevkitjs.dir/cmake_clean.cmake
.PHONY : src/javascript/CMakeFiles/kodidevkitjs.dir/clean

src/javascript/CMakeFiles/kodidevkitjs.dir/depend: src/javascript/kodidevkitjsJAVASCRIPT_wrap.cxx
	cd /home/alwin/Development/kodi-dev-kit/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alwin/Development/kodi-dev-kit /home/alwin/Development/kodi-dev-kit/src/javascript /home/alwin/Development/kodi-dev-kit/build /home/alwin/Development/kodi-dev-kit/build/src/javascript /home/alwin/Development/kodi-dev-kit/build/src/javascript/CMakeFiles/kodidevkitjs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/javascript/CMakeFiles/kodidevkitjs.dir/depend

