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
include src/python/python3/CMakeFiles/_python3-kodidevkit.dir/depend.make

# Include the progress variables for this target.
include src/python/python3/CMakeFiles/_python3-kodidevkit.dir/progress.make

# Include the compile flags for this target's objects.
include src/python/python3/CMakeFiles/_python3-kodidevkit.dir/flags.make

src/python/python3/kodidevkit3PYTHON_wrap.cxx: ../src/python/python3/kodidevkit3.i
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/alwin/Development/kodi-dev-kit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Swig source"
	cd /home/alwin/Development/kodi-dev-kit/build/src/python/python3 && /usr/bin/cmake -E make_directory /home/alwin/Development/kodi-dev-kit/build/src/python/python3
	cd /home/alwin/Development/kodi-dev-kit/build/src/python/python3 && /usr/bin/swig3.0 -python -I/home/alwin/Development/kodi-dev-kit/build/src -outdir /home/alwin/Development/kodi-dev-kit/build/src/python/python3 -c++ -I/home/alwin/Development/kodi-dev-kit/include -o /home/alwin/Development/kodi-dev-kit/build/src/python/python3/kodidevkit3PYTHON_wrap.cxx /home/alwin/Development/kodi-dev-kit/src/python/python3/kodidevkit3.i

src/python/python3/kodi.py: src/python/python3/kodidevkit3PYTHON_wrap.cxx
	@$(CMAKE_COMMAND) -E touch_nocreate src/python/python3/kodi.py

src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o: src/python/python3/CMakeFiles/_python3-kodidevkit.dir/flags.make
src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o: src/python/python3/kodidevkit3PYTHON_wrap.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alwin/Development/kodi-dev-kit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o"
	cd /home/alwin/Development/kodi-dev-kit/build/src/python/python3 && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o -c /home/alwin/Development/kodi-dev-kit/build/src/python/python3/kodidevkit3PYTHON_wrap.cxx

src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.i"
	cd /home/alwin/Development/kodi-dev-kit/build/src/python/python3 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alwin/Development/kodi-dev-kit/build/src/python/python3/kodidevkit3PYTHON_wrap.cxx > CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.i

src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.s"
	cd /home/alwin/Development/kodi-dev-kit/build/src/python/python3 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alwin/Development/kodi-dev-kit/build/src/python/python3/kodidevkit3PYTHON_wrap.cxx -o CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.s

src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o.requires:

.PHONY : src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o.requires

src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o.provides: src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o.requires
	$(MAKE) -f src/python/python3/CMakeFiles/_python3-kodidevkit.dir/build.make src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o.provides.build
.PHONY : src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o.provides

src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o.provides.build: src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o


# Object files for target _python3-kodidevkit
_python3__kodidevkit_OBJECTS = \
"CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o"

# External object files for target _python3-kodidevkit
_python3__kodidevkit_EXTERNAL_OBJECTS =

src/python/python3/_kodi.so: src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o
src/python/python3/_kodi.so: src/python/python3/CMakeFiles/_python3-kodidevkit.dir/build.make
src/python/python3/_kodi.so: /usr/lib/x86_64-linux-gnu/libpython3.5m.so
src/python/python3/_kodi.so: src/libkodidevkit.a
src/python/python3/_kodi.so: src/python/python3/CMakeFiles/_python3-kodidevkit.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alwin/Development/kodi-dev-kit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared module _kodi.so"
	cd /home/alwin/Development/kodi-dev-kit/build/src/python/python3 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_python3-kodidevkit.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/python/python3/CMakeFiles/_python3-kodidevkit.dir/build: src/python/python3/_kodi.so

.PHONY : src/python/python3/CMakeFiles/_python3-kodidevkit.dir/build

src/python/python3/CMakeFiles/_python3-kodidevkit.dir/requires: src/python/python3/CMakeFiles/_python3-kodidevkit.dir/kodidevkit3PYTHON_wrap.cxx.o.requires

.PHONY : src/python/python3/CMakeFiles/_python3-kodidevkit.dir/requires

src/python/python3/CMakeFiles/_python3-kodidevkit.dir/clean:
	cd /home/alwin/Development/kodi-dev-kit/build/src/python/python3 && $(CMAKE_COMMAND) -P CMakeFiles/_python3-kodidevkit.dir/cmake_clean.cmake
.PHONY : src/python/python3/CMakeFiles/_python3-kodidevkit.dir/clean

src/python/python3/CMakeFiles/_python3-kodidevkit.dir/depend: src/python/python3/kodidevkit3PYTHON_wrap.cxx
src/python/python3/CMakeFiles/_python3-kodidevkit.dir/depend: src/python/python3/kodi.py
	cd /home/alwin/Development/kodi-dev-kit/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alwin/Development/kodi-dev-kit /home/alwin/Development/kodi-dev-kit/src/python/python3 /home/alwin/Development/kodi-dev-kit/build /home/alwin/Development/kodi-dev-kit/build/src/python/python3 /home/alwin/Development/kodi-dev-kit/build/src/python/python3/CMakeFiles/_python3-kodidevkit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/python/python3/CMakeFiles/_python3-kodidevkit.dir/depend
