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
include CMakeFiles/argsThread.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/argsThread.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/argsThread.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/argsThread.dir/flags.make

CMakeFiles/argsThread.dir/argsThread.cpp.o: CMakeFiles/argsThread.dir/flags.make
CMakeFiles/argsThread.dir/argsThread.cpp.o: ../argsThread.cpp
CMakeFiles/argsThread.dir/argsThread.cpp.o: CMakeFiles/argsThread.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/m.sukhanov1/Tasks/Task3/Example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/argsThread.dir/argsThread.cpp.o"
	/opt/nvidia/hpc_sdk/Linux_x86_64/23.11/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/argsThread.dir/argsThread.cpp.o -MF CMakeFiles/argsThread.dir/argsThread.cpp.o.d -o CMakeFiles/argsThread.dir/argsThread.cpp.o -c /home/m.sukhanov1/Tasks/Task3/Example/argsThread.cpp

CMakeFiles/argsThread.dir/argsThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/argsThread.dir/argsThread.cpp.i"
	/opt/nvidia/hpc_sdk/Linux_x86_64/23.11/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/m.sukhanov1/Tasks/Task3/Example/argsThread.cpp > CMakeFiles/argsThread.dir/argsThread.cpp.i

CMakeFiles/argsThread.dir/argsThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/argsThread.dir/argsThread.cpp.s"
	/opt/nvidia/hpc_sdk/Linux_x86_64/23.11/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/m.sukhanov1/Tasks/Task3/Example/argsThread.cpp -o CMakeFiles/argsThread.dir/argsThread.cpp.s

# Object files for target argsThread
argsThread_OBJECTS = \
"CMakeFiles/argsThread.dir/argsThread.cpp.o"

# External object files for target argsThread
argsThread_EXTERNAL_OBJECTS =

bin/nvc++/argsThread: CMakeFiles/argsThread.dir/argsThread.cpp.o
bin/nvc++/argsThread: CMakeFiles/argsThread.dir/build.make
bin/nvc++/argsThread: CMakeFiles/argsThread.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/m.sukhanov1/Tasks/Task3/Example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/nvc++/argsThread"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/argsThread.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/argsThread.dir/build: bin/nvc++/argsThread
.PHONY : CMakeFiles/argsThread.dir/build

CMakeFiles/argsThread.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/argsThread.dir/cmake_clean.cmake
.PHONY : CMakeFiles/argsThread.dir/clean

CMakeFiles/argsThread.dir/depend:
	cd /home/m.sukhanov1/Tasks/Task3/Example/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/m.sukhanov1/Tasks/Task3/Example /home/m.sukhanov1/Tasks/Task3/Example /home/m.sukhanov1/Tasks/Task3/Example/build /home/m.sukhanov1/Tasks/Task3/Example/build /home/m.sukhanov1/Tasks/Task3/Example/build/CMakeFiles/argsThread.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/argsThread.dir/depend

