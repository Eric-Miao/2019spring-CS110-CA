# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /home/eric/Downloads/clion-2018.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/eric/Downloads/clion-2018.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/eric/Desktop/ca/hw/hw5/method2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eric/Desktop/ca/hw/hw5/method2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/method2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/method2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/method2.dir/flags.make

CMakeFiles/method2.dir/main.c.o: CMakeFiles/method2.dir/flags.make
CMakeFiles/method2.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/Desktop/ca/hw/hw5/method2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/method2.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/method2.dir/main.c.o   -c /home/eric/Desktop/ca/hw/hw5/method2/main.c

CMakeFiles/method2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/method2.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/eric/Desktop/ca/hw/hw5/method2/main.c > CMakeFiles/method2.dir/main.c.i

CMakeFiles/method2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/method2.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/eric/Desktop/ca/hw/hw5/method2/main.c -o CMakeFiles/method2.dir/main.c.s

# Object files for target method2
method2_OBJECTS = \
"CMakeFiles/method2.dir/main.c.o"

# External object files for target method2
method2_EXTERNAL_OBJECTS =

method2: CMakeFiles/method2.dir/main.c.o
method2: CMakeFiles/method2.dir/build.make
method2: CMakeFiles/method2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/eric/Desktop/ca/hw/hw5/method2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable method2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/method2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/method2.dir/build: method2

.PHONY : CMakeFiles/method2.dir/build

CMakeFiles/method2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/method2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/method2.dir/clean

CMakeFiles/method2.dir/depend:
	cd /home/eric/Desktop/ca/hw/hw5/method2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eric/Desktop/ca/hw/hw5/method2 /home/eric/Desktop/ca/hw/hw5/method2 /home/eric/Desktop/ca/hw/hw5/method2/cmake-build-debug /home/eric/Desktop/ca/hw/hw5/method2/cmake-build-debug /home/eric/Desktop/ca/hw/hw5/method2/cmake-build-debug/CMakeFiles/method2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/method2.dir/depend
