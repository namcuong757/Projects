# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/TranCuong/Projects/Library_Management/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/TranCuong/Projects/Library_Management/src/build

# Include any dependencies generated for this target.
include CMakeFiles/library.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/library.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/library.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/library.dir/flags.make

CMakeFiles/library.dir/main.cpp.o: CMakeFiles/library.dir/flags.make
CMakeFiles/library.dir/main.cpp.o: ../main.cpp
CMakeFiles/library.dir/main.cpp.o: CMakeFiles/library.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/TranCuong/Projects/Library_Management/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/library.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/library.dir/main.cpp.o -MF CMakeFiles/library.dir/main.cpp.o.d -o CMakeFiles/library.dir/main.cpp.o -c /Users/TranCuong/Projects/Library_Management/src/main.cpp

CMakeFiles/library.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/library.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/TranCuong/Projects/Library_Management/src/main.cpp > CMakeFiles/library.dir/main.cpp.i

CMakeFiles/library.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/library.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/TranCuong/Projects/Library_Management/src/main.cpp -o CMakeFiles/library.dir/main.cpp.s

# Object files for target library
library_OBJECTS = \
"CMakeFiles/library.dir/main.cpp.o"

# External object files for target library
library_EXTERNAL_OBJECTS =

library: CMakeFiles/library.dir/main.cpp.o
library: CMakeFiles/library.dir/build.make
library: libtool-help.a
library: CMakeFiles/library.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/TranCuong/Projects/Library_Management/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable library"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/library.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/library.dir/build: library
.PHONY : CMakeFiles/library.dir/build

CMakeFiles/library.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/library.dir/cmake_clean.cmake
.PHONY : CMakeFiles/library.dir/clean

CMakeFiles/library.dir/depend:
	cd /Users/TranCuong/Projects/Library_Management/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/TranCuong/Projects/Library_Management/src /Users/TranCuong/Projects/Library_Management/src /Users/TranCuong/Projects/Library_Management/src/build /Users/TranCuong/Projects/Library_Management/src/build /Users/TranCuong/Projects/Library_Management/src/build/CMakeFiles/library.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/library.dir/depend

