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
CMAKE_COMMAND = /home/pdata/Apps/clion-2017.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/pdata/Apps/clion-2017.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/process_communication.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/process_communication.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/process_communication.dir/flags.make

CMakeFiles/process_communication.dir/main.cpp.o: CMakeFiles/process_communication.dir/flags.make
CMakeFiles/process_communication.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/process_communication.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/process_communication.dir/main.cpp.o -c /home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication/main.cpp

CMakeFiles/process_communication.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/process_communication.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication/main.cpp > CMakeFiles/process_communication.dir/main.cpp.i

CMakeFiles/process_communication.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/process_communication.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication/main.cpp -o CMakeFiles/process_communication.dir/main.cpp.s

CMakeFiles/process_communication.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/process_communication.dir/main.cpp.o.requires

CMakeFiles/process_communication.dir/main.cpp.o.provides: CMakeFiles/process_communication.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/process_communication.dir/build.make CMakeFiles/process_communication.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/process_communication.dir/main.cpp.o.provides

CMakeFiles/process_communication.dir/main.cpp.o.provides.build: CMakeFiles/process_communication.dir/main.cpp.o


CMakeFiles/process_communication.dir/SocketServer.cpp.o: CMakeFiles/process_communication.dir/flags.make
CMakeFiles/process_communication.dir/SocketServer.cpp.o: ../SocketServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/process_communication.dir/SocketServer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/process_communication.dir/SocketServer.cpp.o -c /home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication/SocketServer.cpp

CMakeFiles/process_communication.dir/SocketServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/process_communication.dir/SocketServer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication/SocketServer.cpp > CMakeFiles/process_communication.dir/SocketServer.cpp.i

CMakeFiles/process_communication.dir/SocketServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/process_communication.dir/SocketServer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication/SocketServer.cpp -o CMakeFiles/process_communication.dir/SocketServer.cpp.s

CMakeFiles/process_communication.dir/SocketServer.cpp.o.requires:

.PHONY : CMakeFiles/process_communication.dir/SocketServer.cpp.o.requires

CMakeFiles/process_communication.dir/SocketServer.cpp.o.provides: CMakeFiles/process_communication.dir/SocketServer.cpp.o.requires
	$(MAKE) -f CMakeFiles/process_communication.dir/build.make CMakeFiles/process_communication.dir/SocketServer.cpp.o.provides.build
.PHONY : CMakeFiles/process_communication.dir/SocketServer.cpp.o.provides

CMakeFiles/process_communication.dir/SocketServer.cpp.o.provides.build: CMakeFiles/process_communication.dir/SocketServer.cpp.o


# Object files for target process_communication
process_communication_OBJECTS = \
"CMakeFiles/process_communication.dir/main.cpp.o" \
"CMakeFiles/process_communication.dir/SocketServer.cpp.o"

# External object files for target process_communication
process_communication_EXTERNAL_OBJECTS =

process_communication: CMakeFiles/process_communication.dir/main.cpp.o
process_communication: CMakeFiles/process_communication.dir/SocketServer.cpp.o
process_communication: CMakeFiles/process_communication.dir/build.make
process_communication: CMakeFiles/process_communication.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable process_communication"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/process_communication.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/process_communication.dir/build: process_communication

.PHONY : CMakeFiles/process_communication.dir/build

CMakeFiles/process_communication.dir/requires: CMakeFiles/process_communication.dir/main.cpp.o.requires
CMakeFiles/process_communication.dir/requires: CMakeFiles/process_communication.dir/SocketServer.cpp.o.requires

.PHONY : CMakeFiles/process_communication.dir/requires

CMakeFiles/process_communication.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/process_communication.dir/cmake_clean.cmake
.PHONY : CMakeFiles/process_communication.dir/clean

CMakeFiles/process_communication.dir/depend:
	cd /home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication /home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication /home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication/cmake-build-debug /home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication/cmake-build-debug /home/pdata/Podyplomowka/repos/interprocess_and_interthread_comunication/process-communication/cmake-build-debug/CMakeFiles/process_communication.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/process_communication.dir/depend
