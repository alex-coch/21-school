# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alex/21-school/CPP1_s21_matrixplus-4/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/21-school/CPP1_s21_matrixplus-4/src/build

# Include any dependencies generated for this target.
include CMakeFiles/s21_matrix_oop.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/s21_matrix_oop.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/s21_matrix_oop.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/s21_matrix_oop.dir/flags.make

CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.o: CMakeFiles/s21_matrix_oop.dir/flags.make
CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.o: ../s21_matrix_plus.cc
CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.o: CMakeFiles/s21_matrix_oop.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/21-school/CPP1_s21_matrixplus-4/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.o -MF CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.o.d -o CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.o -c /home/alex/21-school/CPP1_s21_matrixplus-4/src/s21_matrix_plus.cc

CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/21-school/CPP1_s21_matrixplus-4/src/s21_matrix_plus.cc > CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.i

CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/21-school/CPP1_s21_matrixplus-4/src/s21_matrix_plus.cc -o CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.s

# Object files for target s21_matrix_oop
s21_matrix_oop_OBJECTS = \
"CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.o"

# External object files for target s21_matrix_oop
s21_matrix_oop_EXTERNAL_OBJECTS =

s21_matrix_oop.a: CMakeFiles/s21_matrix_oop.dir/s21_matrix_plus.cc.o
s21_matrix_oop.a: CMakeFiles/s21_matrix_oop.dir/build.make
s21_matrix_oop.a: CMakeFiles/s21_matrix_oop.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/21-school/CPP1_s21_matrixplus-4/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library s21_matrix_oop.a"
	$(CMAKE_COMMAND) -P CMakeFiles/s21_matrix_oop.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/s21_matrix_oop.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/s21_matrix_oop.dir/build: s21_matrix_oop.a
.PHONY : CMakeFiles/s21_matrix_oop.dir/build

CMakeFiles/s21_matrix_oop.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/s21_matrix_oop.dir/cmake_clean.cmake
.PHONY : CMakeFiles/s21_matrix_oop.dir/clean

CMakeFiles/s21_matrix_oop.dir/depend:
	cd /home/alex/21-school/CPP1_s21_matrixplus-4/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/21-school/CPP1_s21_matrixplus-4/src /home/alex/21-school/CPP1_s21_matrixplus-4/src /home/alex/21-school/CPP1_s21_matrixplus-4/src/build /home/alex/21-school/CPP1_s21_matrixplus-4/src/build /home/alex/21-school/CPP1_s21_matrixplus-4/src/build/CMakeFiles/s21_matrix_oop.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/s21_matrix_oop.dir/depend

