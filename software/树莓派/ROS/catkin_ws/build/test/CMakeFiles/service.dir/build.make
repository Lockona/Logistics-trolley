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
CMAKE_SOURCE_DIR = /home/kero907/work_space/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kero907/work_space/catkin_ws/build

# Include any dependencies generated for this target.
include test/CMakeFiles/service.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/service.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/service.dir/flags.make

test/CMakeFiles/service.dir/src/service.cpp.o: test/CMakeFiles/service.dir/flags.make
test/CMakeFiles/service.dir/src/service.cpp.o: /home/kero907/work_space/catkin_ws/src/test/src/service.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kero907/work_space/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/service.dir/src/service.cpp.o"
	cd /home/kero907/work_space/catkin_ws/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/service.dir/src/service.cpp.o -c /home/kero907/work_space/catkin_ws/src/test/src/service.cpp

test/CMakeFiles/service.dir/src/service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/service.dir/src/service.cpp.i"
	cd /home/kero907/work_space/catkin_ws/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kero907/work_space/catkin_ws/src/test/src/service.cpp > CMakeFiles/service.dir/src/service.cpp.i

test/CMakeFiles/service.dir/src/service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/service.dir/src/service.cpp.s"
	cd /home/kero907/work_space/catkin_ws/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kero907/work_space/catkin_ws/src/test/src/service.cpp -o CMakeFiles/service.dir/src/service.cpp.s

test/CMakeFiles/service.dir/src/duoji.cpp.o: test/CMakeFiles/service.dir/flags.make
test/CMakeFiles/service.dir/src/duoji.cpp.o: /home/kero907/work_space/catkin_ws/src/test/src/duoji.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kero907/work_space/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/service.dir/src/duoji.cpp.o"
	cd /home/kero907/work_space/catkin_ws/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/service.dir/src/duoji.cpp.o -c /home/kero907/work_space/catkin_ws/src/test/src/duoji.cpp

test/CMakeFiles/service.dir/src/duoji.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/service.dir/src/duoji.cpp.i"
	cd /home/kero907/work_space/catkin_ws/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kero907/work_space/catkin_ws/src/test/src/duoji.cpp > CMakeFiles/service.dir/src/duoji.cpp.i

test/CMakeFiles/service.dir/src/duoji.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/service.dir/src/duoji.cpp.s"
	cd /home/kero907/work_space/catkin_ws/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kero907/work_space/catkin_ws/src/test/src/duoji.cpp -o CMakeFiles/service.dir/src/duoji.cpp.s

# Object files for target service
service_OBJECTS = \
"CMakeFiles/service.dir/src/service.cpp.o" \
"CMakeFiles/service.dir/src/duoji.cpp.o"

# External object files for target service
service_EXTERNAL_OBJECTS =

/home/kero907/work_space/catkin_ws/devel/lib/test/service: test/CMakeFiles/service.dir/src/service.cpp.o
/home/kero907/work_space/catkin_ws/devel/lib/test/service: test/CMakeFiles/service.dir/src/duoji.cpp.o
/home/kero907/work_space/catkin_ws/devel/lib/test/service: test/CMakeFiles/service.dir/build.make
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /opt/ros/noetic/lib/libroscpp.so
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /usr/lib/arm-linux-gnueabihf/libpthread.so
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /usr/lib/arm-linux-gnueabihf/libboost_chrono.so.1.71.0
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /usr/lib/arm-linux-gnueabihf/libboost_filesystem.so.1.71.0
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /opt/ros/noetic/lib/librosconsole.so
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /opt/ros/noetic/lib/librosconsole_log4cxx.so
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /opt/ros/noetic/lib/librosconsole_backend_interface.so
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /usr/lib/arm-linux-gnueabihf/liblog4cxx.so
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /usr/lib/arm-linux-gnueabihf/libboost_regex.so.1.71.0
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /opt/ros/noetic/lib/libxmlrpcpp.so
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /opt/ros/noetic/lib/libroscpp_serialization.so
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /opt/ros/noetic/lib/librostime.so
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so.1.71.0
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /opt/ros/noetic/lib/libcpp_common.so
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /usr/lib/arm-linux-gnueabihf/libboost_system.so.1.71.0
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /usr/lib/arm-linux-gnueabihf/libboost_thread.so.1.71.0
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so.0.4
/home/kero907/work_space/catkin_ws/devel/lib/test/service: /home/kero907/work_space/catkin_ws/devel/lib/libwiringPi.so
/home/kero907/work_space/catkin_ws/devel/lib/test/service: test/CMakeFiles/service.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kero907/work_space/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /home/kero907/work_space/catkin_ws/devel/lib/test/service"
	cd /home/kero907/work_space/catkin_ws/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/service.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/service.dir/build: /home/kero907/work_space/catkin_ws/devel/lib/test/service

.PHONY : test/CMakeFiles/service.dir/build

test/CMakeFiles/service.dir/clean:
	cd /home/kero907/work_space/catkin_ws/build/test && $(CMAKE_COMMAND) -P CMakeFiles/service.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/service.dir/clean

test/CMakeFiles/service.dir/depend:
	cd /home/kero907/work_space/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kero907/work_space/catkin_ws/src /home/kero907/work_space/catkin_ws/src/test /home/kero907/work_space/catkin_ws/build /home/kero907/work_space/catkin_ws/build/test /home/kero907/work_space/catkin_ws/build/test/CMakeFiles/service.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/service.dir/depend

