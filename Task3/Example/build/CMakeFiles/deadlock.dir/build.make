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
CMAKE_SOURCE_DIR = /home/m.sukhanov1/Tasks/Task3/Example

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/m.sukhanov1/Tasks/Task3/Example/build

# Include any dependencies generated for this target.
include CMakeFiles/deadlock.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/deadlock.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/deadlock.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/deadlock.dir/flags.make

CMakeFiles/deadlock.dir/deadlock.cpp.o: CMakeFiles/deadlock.dir/flags.make
CMakeFiles/deadlock.dir/deadlock.cpp.o: ../deadlock.cpp
CMakeFiles/deadlock.dir/deadlock.cpp.o: CMakeFiles/deadlock.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/m.sukhanov1/Tasks/Task3/Example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/deadlock.dir/deadlock.cpp.o"
	/opt/nvidia/hpc_sdk/Linux_x86_64/23.11/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/deadlock.dir/deadlock.cpp.o -MF CMakeFiles/deadlock.dir/deadlock.cpp.o.d -o CMakeFiles/deadlock.dir/deadlock.cpp.o -c /home/m.sukhanov1/Tasks/Task3/Example/deadlock.cpp

CMakeFiles/deadlock.dir/deadlock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/deadlock.dir/deadlock.cpp.i"
	/opt/nvidia/hpc_sdk/Linux_x86_64/23.11/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/m.sukhanov1/Tasks/Task3/Example/deadlock.cpp > CMakeFiles/deadlock.dir/deadlock.cpp.i

CMakeFiles/deadlock.dir/deadlock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/deadlock.dir/deadlock.cpp.s"
	/opt/nvidia/hpc_sdk/Linux_x86_64/23.11/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/m.sukhanov1/Tasks/Task3/Example/deadlock.cpp -o CMakeFiles/deadlock.dir/deadlock.cpp.s

# Object files for target deadlock
deadlock_OBJECTS = \
"CMakeFiles/deadlock.dir/deadlock.cpp.o"

# External object files for target deadlock
deadlock_EXTERNAL_OBJECTS =

bin/nvc++/deadlock: CMakeFiles/deadlock.dir/deadlock.cpp.o
bin/nvc++/deadlock: CMakeFiles/deadlock.dir/build.make
bin/nvc++/deadlock: CMakeFiles/deadlock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/m.sukhanov1/Tasks/Task3/Example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/nvc++/deadlock"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/deadlock.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/deadlock.dir/build: bin/nvc++/deadlock
.PHONY : CMakeFiles/deadlock.dir/build

CMakeFiles/deadlock.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/deadlock.dir/cmake_clean.cmake
.PHONY : CMakeFiles/deadlock.dir/clean

CMakeFiles/deadlock.dir/depend:
	cd /home/m.sukhanov1/Tasks/Task3/Example/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/m.sukhanov1/Tasks/Task3/Example /home/m.sukhanov1/Tasks/Task3/Example /home/m.sukhanov1/Tasks/Task3/Example/build /home/m.sukhanov1/Tasks/Task3/Example/build /home/m.sukhanov1/Tasks/Task3/Example/build/CMakeFiles/deadlock.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/deadlock.dir/depend

