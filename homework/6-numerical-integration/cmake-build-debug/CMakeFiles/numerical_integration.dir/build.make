# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/marc/Documents/clion-2019.3.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/marc/Documents/clion-2019.3.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/numerical_integration.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/numerical_integration.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/numerical_integration.dir/flags.make

CMakeFiles/numerical_integration.dir/main.c.o: CMakeFiles/numerical_integration.dir/flags.make
CMakeFiles/numerical_integration.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/numerical_integration.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/numerical_integration.dir/main.c.o   -c /home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration/main.c

CMakeFiles/numerical_integration.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/numerical_integration.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration/main.c > CMakeFiles/numerical_integration.dir/main.c.i

CMakeFiles/numerical_integration.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/numerical_integration.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration/main.c -o CMakeFiles/numerical_integration.dir/main.c.s

CMakeFiles/numerical_integration.dir/integration.c.o: CMakeFiles/numerical_integration.dir/flags.make
CMakeFiles/numerical_integration.dir/integration.c.o: ../integration.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/numerical_integration.dir/integration.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/numerical_integration.dir/integration.c.o   -c /home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration/integration.c

CMakeFiles/numerical_integration.dir/integration.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/numerical_integration.dir/integration.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration/integration.c > CMakeFiles/numerical_integration.dir/integration.c.i

CMakeFiles/numerical_integration.dir/integration.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/numerical_integration.dir/integration.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration/integration.c -o CMakeFiles/numerical_integration.dir/integration.c.s

# Object files for target numerical_integration
numerical_integration_OBJECTS = \
"CMakeFiles/numerical_integration.dir/main.c.o" \
"CMakeFiles/numerical_integration.dir/integration.c.o"

# External object files for target numerical_integration
numerical_integration_EXTERNAL_OBJECTS =

numerical_integration: CMakeFiles/numerical_integration.dir/main.c.o
numerical_integration: CMakeFiles/numerical_integration.dir/integration.c.o
numerical_integration: CMakeFiles/numerical_integration.dir/build.make
numerical_integration: /usr/local/lib/libgsl.so
numerical_integration: /usr/local/lib/libgslcblas.so
numerical_integration: CMakeFiles/numerical_integration.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable numerical_integration"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/numerical_integration.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/numerical_integration.dir/build: numerical_integration

.PHONY : CMakeFiles/numerical_integration.dir/build

CMakeFiles/numerical_integration.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/numerical_integration.dir/cmake_clean.cmake
.PHONY : CMakeFiles/numerical_integration.dir/clean

CMakeFiles/numerical_integration.dir/depend:
	cd /home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration /home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration /home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration/cmake-build-debug /home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration/cmake-build-debug /home/marc/Dropbox/repos/ppnm/homework/6-numerical-integration/cmake-build-debug/CMakeFiles/numerical_integration.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/numerical_integration.dir/depend

