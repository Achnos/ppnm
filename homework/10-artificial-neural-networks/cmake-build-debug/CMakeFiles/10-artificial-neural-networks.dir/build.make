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
CMAKE_SOURCE_DIR = /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/10-artificial-neural-networks.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/10-artificial-neural-networks.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/10-artificial-neural-networks.dir/flags.make

CMakeFiles/10-artificial-neural-networks.dir/main.c.o: CMakeFiles/10-artificial-neural-networks.dir/flags.make
CMakeFiles/10-artificial-neural-networks.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/10-artificial-neural-networks.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/10-artificial-neural-networks.dir/main.c.o   -c /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/main.c

CMakeFiles/10-artificial-neural-networks.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/10-artificial-neural-networks.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/main.c > CMakeFiles/10-artificial-neural-networks.dir/main.c.i

CMakeFiles/10-artificial-neural-networks.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/10-artificial-neural-networks.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/main.c -o CMakeFiles/10-artificial-neural-networks.dir/main.c.s

CMakeFiles/10-artificial-neural-networks.dir/neuralnetwork.c.o: CMakeFiles/10-artificial-neural-networks.dir/flags.make
CMakeFiles/10-artificial-neural-networks.dir/neuralnetwork.c.o: ../neuralnetwork.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/10-artificial-neural-networks.dir/neuralnetwork.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/10-artificial-neural-networks.dir/neuralnetwork.c.o   -c /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/neuralnetwork.c

CMakeFiles/10-artificial-neural-networks.dir/neuralnetwork.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/10-artificial-neural-networks.dir/neuralnetwork.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/neuralnetwork.c > CMakeFiles/10-artificial-neural-networks.dir/neuralnetwork.c.i

CMakeFiles/10-artificial-neural-networks.dir/neuralnetwork.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/10-artificial-neural-networks.dir/neuralnetwork.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/neuralnetwork.c -o CMakeFiles/10-artificial-neural-networks.dir/neuralnetwork.c.s

CMakeFiles/10-artificial-neural-networks.dir/minimization.c.o: CMakeFiles/10-artificial-neural-networks.dir/flags.make
CMakeFiles/10-artificial-neural-networks.dir/minimization.c.o: ../minimization.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/10-artificial-neural-networks.dir/minimization.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/10-artificial-neural-networks.dir/minimization.c.o   -c /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/minimization.c

CMakeFiles/10-artificial-neural-networks.dir/minimization.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/10-artificial-neural-networks.dir/minimization.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/minimization.c > CMakeFiles/10-artificial-neural-networks.dir/minimization.c.i

CMakeFiles/10-artificial-neural-networks.dir/minimization.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/10-artificial-neural-networks.dir/minimization.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/minimization.c -o CMakeFiles/10-artificial-neural-networks.dir/minimization.c.s

CMakeFiles/10-artificial-neural-networks.dir/utilities.c.o: CMakeFiles/10-artificial-neural-networks.dir/flags.make
CMakeFiles/10-artificial-neural-networks.dir/utilities.c.o: ../utilities.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/10-artificial-neural-networks.dir/utilities.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/10-artificial-neural-networks.dir/utilities.c.o   -c /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/utilities.c

CMakeFiles/10-artificial-neural-networks.dir/utilities.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/10-artificial-neural-networks.dir/utilities.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/utilities.c > CMakeFiles/10-artificial-neural-networks.dir/utilities.c.i

CMakeFiles/10-artificial-neural-networks.dir/utilities.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/10-artificial-neural-networks.dir/utilities.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/utilities.c -o CMakeFiles/10-artificial-neural-networks.dir/utilities.c.s

CMakeFiles/10-artificial-neural-networks.dir/input2Array.c.o: CMakeFiles/10-artificial-neural-networks.dir/flags.make
CMakeFiles/10-artificial-neural-networks.dir/input2Array.c.o: ../input2Array.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/10-artificial-neural-networks.dir/input2Array.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/10-artificial-neural-networks.dir/input2Array.c.o   -c /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/input2Array.c

CMakeFiles/10-artificial-neural-networks.dir/input2Array.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/10-artificial-neural-networks.dir/input2Array.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/input2Array.c > CMakeFiles/10-artificial-neural-networks.dir/input2Array.c.i

CMakeFiles/10-artificial-neural-networks.dir/input2Array.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/10-artificial-neural-networks.dir/input2Array.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/input2Array.c -o CMakeFiles/10-artificial-neural-networks.dir/input2Array.c.s

# Object files for target 10-artificial-neural-networks
10__artificial__neural__networks_OBJECTS = \
"CMakeFiles/10-artificial-neural-networks.dir/main.c.o" \
"CMakeFiles/10-artificial-neural-networks.dir/neuralnetwork.c.o" \
"CMakeFiles/10-artificial-neural-networks.dir/minimization.c.o" \
"CMakeFiles/10-artificial-neural-networks.dir/utilities.c.o" \
"CMakeFiles/10-artificial-neural-networks.dir/input2Array.c.o"

# External object files for target 10-artificial-neural-networks
10__artificial__neural__networks_EXTERNAL_OBJECTS =

10-artificial-neural-networks: CMakeFiles/10-artificial-neural-networks.dir/main.c.o
10-artificial-neural-networks: CMakeFiles/10-artificial-neural-networks.dir/neuralnetwork.c.o
10-artificial-neural-networks: CMakeFiles/10-artificial-neural-networks.dir/minimization.c.o
10-artificial-neural-networks: CMakeFiles/10-artificial-neural-networks.dir/utilities.c.o
10-artificial-neural-networks: CMakeFiles/10-artificial-neural-networks.dir/input2Array.c.o
10-artificial-neural-networks: CMakeFiles/10-artificial-neural-networks.dir/build.make
10-artificial-neural-networks: /usr/lib/x86_64-linux-gnu/libgsl.so
10-artificial-neural-networks: /usr/lib/x86_64-linux-gnu/libgslcblas.so
10-artificial-neural-networks: CMakeFiles/10-artificial-neural-networks.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable 10-artificial-neural-networks"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/10-artificial-neural-networks.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/10-artificial-neural-networks.dir/build: 10-artificial-neural-networks

.PHONY : CMakeFiles/10-artificial-neural-networks.dir/build

CMakeFiles/10-artificial-neural-networks.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/10-artificial-neural-networks.dir/cmake_clean.cmake
.PHONY : CMakeFiles/10-artificial-neural-networks.dir/clean

CMakeFiles/10-artificial-neural-networks.dir/depend:
	cd /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/cmake-build-debug /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/cmake-build-debug /home/marc/Dropbox/repos/ppnm/homework/10-artificial-neural-networks/cmake-build-debug/CMakeFiles/10-artificial-neural-networks.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/10-artificial-neural-networks.dir/depend

