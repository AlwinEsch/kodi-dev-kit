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
include src/lua/CMakeFiles/kodi-lua.dir/depend.make

# Include the progress variables for this target.
include src/lua/CMakeFiles/kodi-lua.dir/progress.make

# Include the compile flags for this target's objects.
include src/lua/CMakeFiles/kodi-lua.dir/flags.make

src/lua/kodidevkitluaLUA_wrap.cxx: ../src/lua/kodidevkitlua.i
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/alwin/Development/kodi-dev-kit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Swig source"
	cd /home/alwin/Development/kodi-dev-kit/build/src/lua && /usr/bin/cmake -E make_directory /home/alwin/Development/kodi-dev-kit/build/src/lua
	cd /home/alwin/Development/kodi-dev-kit/build/src/lua && /usr/bin/swig3.0 -lua -I/home/alwin/Development/kodi-dev-kit/build/src -outdir /home/alwin/Development/kodi-dev-kit/build/src/lua -c++ -I/home/alwin/Development/kodi-dev-kit/include -o /home/alwin/Development/kodi-dev-kit/build/src/lua/kodidevkitluaLUA_wrap.cxx /home/alwin/Development/kodi-dev-kit/src/lua/kodidevkitlua.i

src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o: src/lua/CMakeFiles/kodi-lua.dir/flags.make
src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o: src/lua/kodidevkitluaLUA_wrap.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alwin/Development/kodi-dev-kit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o"
	cd /home/alwin/Development/kodi-dev-kit/build/src/lua && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o -c /home/alwin/Development/kodi-dev-kit/build/src/lua/kodidevkitluaLUA_wrap.cxx

src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.i"
	cd /home/alwin/Development/kodi-dev-kit/build/src/lua && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alwin/Development/kodi-dev-kit/build/src/lua/kodidevkitluaLUA_wrap.cxx > CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.i

src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.s"
	cd /home/alwin/Development/kodi-dev-kit/build/src/lua && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alwin/Development/kodi-dev-kit/build/src/lua/kodidevkitluaLUA_wrap.cxx -o CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.s

src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o.requires:

.PHONY : src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o.requires

src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o.provides: src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o.requires
	$(MAKE) -f src/lua/CMakeFiles/kodi-lua.dir/build.make src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o.provides.build
.PHONY : src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o.provides

src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o.provides.build: src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o


# Object files for target kodi-lua
kodi__lua_OBJECTS = \
"CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o"

# External object files for target kodi-lua
kodi__lua_EXTERNAL_OBJECTS =

src/lua/kodi-lua.so: src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o
src/lua/kodi-lua.so: src/lua/CMakeFiles/kodi-lua.dir/build.make
src/lua/kodi-lua.so: /usr/lib/x86_64-linux-gnu/liblua5.2.so
src/lua/kodi-lua.so: /usr/lib/x86_64-linux-gnu/libm.so
src/lua/kodi-lua.so: src/libkodidevkit.a
src/lua/kodi-lua.so: src/lua/CMakeFiles/kodi-lua.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alwin/Development/kodi-dev-kit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared module kodi-lua.so"
	cd /home/alwin/Development/kodi-dev-kit/build/src/lua && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kodi-lua.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/lua/CMakeFiles/kodi-lua.dir/build: src/lua/kodi-lua.so

.PHONY : src/lua/CMakeFiles/kodi-lua.dir/build

src/lua/CMakeFiles/kodi-lua.dir/requires: src/lua/CMakeFiles/kodi-lua.dir/kodidevkitluaLUA_wrap.cxx.o.requires

.PHONY : src/lua/CMakeFiles/kodi-lua.dir/requires

src/lua/CMakeFiles/kodi-lua.dir/clean:
	cd /home/alwin/Development/kodi-dev-kit/build/src/lua && $(CMAKE_COMMAND) -P CMakeFiles/kodi-lua.dir/cmake_clean.cmake
.PHONY : src/lua/CMakeFiles/kodi-lua.dir/clean

src/lua/CMakeFiles/kodi-lua.dir/depend: src/lua/kodidevkitluaLUA_wrap.cxx
	cd /home/alwin/Development/kodi-dev-kit/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alwin/Development/kodi-dev-kit /home/alwin/Development/kodi-dev-kit/src/lua /home/alwin/Development/kodi-dev-kit/build /home/alwin/Development/kodi-dev-kit/build/src/lua /home/alwin/Development/kodi-dev-kit/build/src/lua/CMakeFiles/kodi-lua.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/lua/CMakeFiles/kodi-lua.dir/depend
