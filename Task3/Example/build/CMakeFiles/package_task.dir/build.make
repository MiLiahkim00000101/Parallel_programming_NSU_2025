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
include CMakeFiles/package_task.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/package_task.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/package_task.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/package_task.dir/flags.make

CMakeFiles/package_task.dir/package_task.cpp.o: CMakeFiles/package_task.dir/flags.make
CMakeFiles/package_task.dir/package_task.cpp.o: ../package_task.cpp
CMakeFiles/package_task.dir/package_task.cpp.o: CMakeFiles/package_task.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/m.sukhanov1/Tasks/Task3/Example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/package_task.dir/package_task.cpp.o"
	/opt/nvidia/hpc_sdk/Linux_x86_64/23.11/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/package_task.dir/package_task.cpp.o -MF CMakeFiles/package_task.dir/package_task.cpp.o.d -o CMakeFiles/package_task.dir/package_task.cpp.o -c /home/m.sukhanov1/Tasks/Task3/Example/package_task.cpp

CMakeFiles/package_task.dir/package_task.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/package_task.dir/package_task.cpp.i"
	/opt/nvidia/hpc_sdk/Linux_x86_64/23.11/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/m.sukhanov1/Tasks/Task3/Example/package_task.cpp > CMakeFiles/package_task.dir/package_task.cpp.i

CMakeFiles/package_task.dir/package_task.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/package_task.dir/package_task.cpp.s"
	/opt/nvidia/hpc_sdk/Linux_x86_64/23.11/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/m.sukhanov1/Tasks/Task3/Example/package_task.cpp -o CMakeFiles/package_task.dir/package_task.cpp.s

# Object files for target package_task
package_task_OBJECTS = \
"CMakeFiles/package_task.dir/package_task.cpp.o"

# External object files for target package_task
package_task_EXTERNAL_OBJECTS =

bin/nvc++/package_task: CMakeFiles/package_task.dir/package_task.cpp.o
bin/nvc++/package_task: CMakeFiles/package_task.dir/build.make
bin/nvc++/package_task: CMakeFiles/package_task.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/m.sukhanov1/Tasks/Task3/Example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/nvc++/package_task"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/package_task.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/package_task.dir/build: bin/nvc++/package_task
.PHONY : CMakeFiles/package_task.dir/build

CMakeFiles/package_task.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/package_task.dir/cmake_clean.cmake
.PHONY : CMakeFiles/package_task.dir/clean

CMakeFiles/package_task.dir/depend:
	cd /home/m.sukhanov1/Tasks/Task3/Example/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/m.sukhanov1/Tasks/Task3/Example /home/m.sukhanov1/Tasks/Task3/Example /home/m.sukhanov1/Tasks/Task3/Example/build /home/m.sukhanov1/Tasks/Task3/Example/build /home/m.sukhanov1/Tasks/Task3/Example/build/CMakeFiles/package_task.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/package_task.dir/depend

