# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /snap/clion/129/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/129/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/n2k/CLionProjects/spbu-semester1-fractals

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/n2k/CLionProjects/spbu-semester1-fractals/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/spbu-semester1-fractals.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/spbu-semester1-fractals.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/spbu-semester1-fractals.dir/flags.make

CMakeFiles/spbu-semester1-fractals.dir/main.cpp.o: CMakeFiles/spbu-semester1-fractals.dir/flags.make
CMakeFiles/spbu-semester1-fractals.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/n2k/CLionProjects/spbu-semester1-fractals/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/spbu-semester1-fractals.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/spbu-semester1-fractals.dir/main.cpp.o -c /home/n2k/CLionProjects/spbu-semester1-fractals/main.cpp

CMakeFiles/spbu-semester1-fractals.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spbu-semester1-fractals.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/n2k/CLionProjects/spbu-semester1-fractals/main.cpp > CMakeFiles/spbu-semester1-fractals.dir/main.cpp.i

CMakeFiles/spbu-semester1-fractals.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spbu-semester1-fractals.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/n2k/CLionProjects/spbu-semester1-fractals/main.cpp -o CMakeFiles/spbu-semester1-fractals.dir/main.cpp.s

# Object files for target spbu-semester1-fractals
spbu__semester1__fractals_OBJECTS = \
"CMakeFiles/spbu-semester1-fractals.dir/main.cpp.o"

# External object files for target spbu-semester1-fractals
spbu__semester1__fractals_EXTERNAL_OBJECTS =

spbu-semester1-fractals: CMakeFiles/spbu-semester1-fractals.dir/main.cpp.o
spbu-semester1-fractals: CMakeFiles/spbu-semester1-fractals.dir/build.make
spbu-semester1-fractals: /usr/lib/x86_64-linux-gnu/libsfml-system.so
spbu-semester1-fractals: /usr/lib/x86_64-linux-gnu/libsfml-window.so
spbu-semester1-fractals: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
spbu-semester1-fractals: /usr/lib/x86_64-linux-gnu/libsfml-network.so
spbu-semester1-fractals: /usr/lib/x86_64-linux-gnu/libsfml-audio.so
spbu-semester1-fractals: CMakeFiles/spbu-semester1-fractals.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/n2k/CLionProjects/spbu-semester1-fractals/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable spbu-semester1-fractals"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/spbu-semester1-fractals.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/spbu-semester1-fractals.dir/build: spbu-semester1-fractals

.PHONY : CMakeFiles/spbu-semester1-fractals.dir/build

CMakeFiles/spbu-semester1-fractals.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/spbu-semester1-fractals.dir/cmake_clean.cmake
.PHONY : CMakeFiles/spbu-semester1-fractals.dir/clean

CMakeFiles/spbu-semester1-fractals.dir/depend:
	cd /home/n2k/CLionProjects/spbu-semester1-fractals/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/n2k/CLionProjects/spbu-semester1-fractals /home/n2k/CLionProjects/spbu-semester1-fractals /home/n2k/CLionProjects/spbu-semester1-fractals/cmake-build-debug /home/n2k/CLionProjects/spbu-semester1-fractals/cmake-build-debug /home/n2k/CLionProjects/spbu-semester1-fractals/cmake-build-debug/CMakeFiles/spbu-semester1-fractals.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/spbu-semester1-fractals.dir/depend

