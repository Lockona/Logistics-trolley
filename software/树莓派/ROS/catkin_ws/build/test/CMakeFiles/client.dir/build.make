# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kero/workspace/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kero/workspace/catkin_ws/build

# Include any dependencies generated for this target.
include test/CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/client.dir/flags.make

test/CMakeFiles/client.dir/src/client.cpp.o: test/CMakeFiles/client.dir/flags.make
test/CMakeFiles/client.dir/src/client.cpp.o: /home/kero/workspace/catkin_ws/src/test/src/client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kero/workspace/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/client.dir/src/client.cpp.o"
	cd /home/kero/workspace/catkin_ws/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/src/client.cpp.o -c /home/kero/workspace/catkin_ws/src/test/src/client.cpp

test/CMakeFiles/client.dir/src/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/src/client.cpp.i"
	cd /home/kero/workspace/catkin_ws/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kero/workspace/catkin_ws/src/test/src/client.cpp > CMakeFiles/client.dir/src/client.cpp.i

test/CMakeFiles/client.dir/src/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/src/client.cpp.s"
	cd /home/kero/workspace/catkin_ws/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kero/workspace/catkin_ws/src/test/src/client.cpp -o CMakeFiles/client.dir/src/client.cpp.s

test/CMakeFiles/client.dir/src/serial_port.cpp.o: test/CMakeFiles/client.dir/flags.make
test/CMakeFiles/client.dir/src/serial_port.cpp.o: /home/kero/workspace/catkin_ws/src/test/src/serial_port.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kero/workspace/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/client.dir/src/serial_port.cpp.o"
	cd /home/kero/workspace/catkin_ws/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/src/serial_port.cpp.o -c /home/kero/workspace/catkin_ws/src/test/src/serial_port.cpp

test/CMakeFiles/client.dir/src/serial_port.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/src/serial_port.cpp.i"
	cd /home/kero/workspace/catkin_ws/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kero/workspace/catkin_ws/src/test/src/serial_port.cpp > CMakeFiles/client.dir/src/serial_port.cpp.i

test/CMakeFiles/client.dir/src/serial_port.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/src/serial_port.cpp.s"
	cd /home/kero/workspace/catkin_ws/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kero/workspace/catkin_ws/src/test/src/serial_port.cpp -o CMakeFiles/client.dir/src/serial_port.cpp.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/src/client.cpp.o" \
"CMakeFiles/client.dir/src/serial_port.cpp.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

/home/kero/workspace/catkin_ws/devel/lib/test/client: test/CMakeFiles/client.dir/src/client.cpp.o
/home/kero/workspace/catkin_ws/devel/lib/test/client: test/CMakeFiles/client.dir/src/serial_port.cpp.o
/home/kero/workspace/catkin_ws/devel/lib/test/client: test/CMakeFiles/client.dir/build.make
/home/kero/workspace/catkin_ws/devel/lib/test/client: /opt/ros/noetic/lib/libroscpp.so
/home/kero/workspace/catkin_ws/devel/lib/test/client: /usr/lib/arm-linux-gnueabihf/libpthread.so
/home/kero/workspace/catkin_ws/devel/lib/test/client: /usr/lib/arm-linux-gnueabihf/libboost_chrono.so.1.71.0
/home/kero/workspace/catkin_ws/devel/lib/test/client: /usr/lib/arm-linux-gnueabihf/libboost_filesystem.so.1.71.0
/home/kero/workspace/catkin_ws/devel/lib/test/client: /opt/ros/noetic/lib/librosconsole.so
/home/kero/workspace/catkin_ws/devel/lib/test/client: /opt/ros/noetic/lib/librosconsole_log4cxx.so
/home/kero/workspace/catkin_ws/devel/lib/test/client: /opt/ros/noetic/lib/librosconsole_backend_interface.so
/home/kero/workspace/catkin_ws/devel/lib/test/client: /usr/lib/arm-linux-gnueabihf/liblog4cxx.so
/home/kero/workspace/catkin_ws/devel/lib/test/client: /usr/lib/arm-linux-gnueabihf/libboost_regex.so.1.71.0
/home/kero/workspace/catkin_ws/devel/lib/test/client: /opt/ros/noetic/lib/libxmlrpcpp.so
/home/kero/workspace/catkin_ws/devel/lib/test/client: /opt/ros/noetic/lib/libroscpp_serialization.so
/home/kero/workspace/catkin_ws/devel/lib/test/client: /opt/ros/noetic/lib/librostime.so
/home/kero/workspace/catkin_ws/devel/lib/test/client: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so.1.71.0
/home/kero/workspace/catkin_ws/devel/lib/test/client: /opt/ros/noetic/lib/libcpp_common.so
/home/kero/workspace/catkin_ws/devel/lib/test/client: /usr/lib/arm-linux-gnueabihf/libboost_system.so.1.71.0
/home/kero/workspace/catkin_ws/devel/lib/test/client: /usr/lib/arm-linux-gnueabihf/libboost_thread.so.1.71.0
/home/kero/workspace/catkin_ws/devel/lib/test/client: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so.0.4
/home/kero/workspace/catkin_ws/devel/lib/test/client: test/CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kero/workspace/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /home/kero/workspace/catkin_ws/devel/lib/test/client"
	cd /home/kero/workspace/catkin_ws/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/client.dir/build: /home/kero/workspace/catkin_ws/devel/lib/test/client

.PHONY : test/CMakeFiles/client.dir/build

test/CMakeFiles/client.dir/clean:
	cd /home/kero/workspace/catkin_ws/build/test && $(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/client.dir/clean

test/CMakeFiles/client.dir/depend:
	cd /home/kero/workspace/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kero/workspace/catkin_ws/src /home/kero/workspace/catkin_ws/src/test /home/kero/workspace/catkin_ws/build /home/kero/workspace/catkin_ws/build/test /home/kero/workspace/catkin_ws/build/test/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/client.dir/depend

