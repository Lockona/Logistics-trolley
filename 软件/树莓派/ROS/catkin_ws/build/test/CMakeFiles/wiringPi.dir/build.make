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
CMAKE_SOURCE_DIR = /home/ubuntu/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/catkin_ws/build

# Include any dependencies generated for this target.
include test/CMakeFiles/wiringPi.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/wiringPi.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/wiringPi.dir/flags.make

test/CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/wiringPi.c.o: test/CMakeFiles/wiringPi.dir/flags.make
test/CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/wiringPi.c.o: /home/ubuntu/WiringPi/wiringPi/wiringPi.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object test/CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/wiringPi.c.o"
	cd /home/ubuntu/catkin_ws/build/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/wiringPi.c.o   -c /home/ubuntu/WiringPi/wiringPi/wiringPi.c

test/CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/wiringPi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/wiringPi.c.i"
	cd /home/ubuntu/catkin_ws/build/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/WiringPi/wiringPi/wiringPi.c > CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/wiringPi.c.i

test/CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/wiringPi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/wiringPi.c.s"
	cd /home/ubuntu/catkin_ws/build/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/WiringPi/wiringPi/wiringPi.c -o CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/wiringPi.c.s

test/CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/softPwm.c.o: test/CMakeFiles/wiringPi.dir/flags.make
test/CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/softPwm.c.o: /home/ubuntu/WiringPi/wiringPi/softPwm.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object test/CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/softPwm.c.o"
	cd /home/ubuntu/catkin_ws/build/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/softPwm.c.o   -c /home/ubuntu/WiringPi/wiringPi/softPwm.c

test/CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/softPwm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/softPwm.c.i"
	cd /home/ubuntu/catkin_ws/build/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/WiringPi/wiringPi/softPwm.c > CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/softPwm.c.i

test/CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/softPwm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/softPwm.c.s"
	cd /home/ubuntu/catkin_ws/build/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/WiringPi/wiringPi/softPwm.c -o CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/softPwm.c.s

# Object files for target wiringPi
wiringPi_OBJECTS = \
"CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/wiringPi.c.o" \
"CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/softPwm.c.o"

# External object files for target wiringPi
wiringPi_EXTERNAL_OBJECTS =

/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: test/CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/wiringPi.c.o
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: test/CMakeFiles/wiringPi.dir/home/ubuntu/WiringPi/wiringPi/softPwm.c.o
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: test/CMakeFiles/wiringPi.dir/build.make
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /opt/ros/noetic/lib/libroscpp.so
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /usr/lib/aarch64-linux-gnu/libpthread.so
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /usr/lib/aarch64-linux-gnu/libboost_chrono.so.1.71.0
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /usr/lib/aarch64-linux-gnu/libboost_filesystem.so.1.71.0
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /opt/ros/noetic/lib/librosconsole.so
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /opt/ros/noetic/lib/librosconsole_log4cxx.so
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /opt/ros/noetic/lib/librosconsole_backend_interface.so
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /usr/lib/aarch64-linux-gnu/liblog4cxx.so
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /usr/lib/aarch64-linux-gnu/libboost_regex.so.1.71.0
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /opt/ros/noetic/lib/libxmlrpcpp.so
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /opt/ros/noetic/lib/libroscpp_serialization.so
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /opt/ros/noetic/lib/librostime.so
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /usr/lib/aarch64-linux-gnu/libboost_date_time.so.1.71.0
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /opt/ros/noetic/lib/libcpp_common.so
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /usr/lib/aarch64-linux-gnu/libboost_system.so.1.71.0
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /usr/lib/aarch64-linux-gnu/libboost_thread.so.1.71.0
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: /usr/lib/aarch64-linux-gnu/libconsole_bridge.so.0.4
/home/ubuntu/catkin_ws/devel/lib/libwiringPi.so: test/CMakeFiles/wiringPi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C shared library /home/ubuntu/catkin_ws/devel/lib/libwiringPi.so"
	cd /home/ubuntu/catkin_ws/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wiringPi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/wiringPi.dir/build: /home/ubuntu/catkin_ws/devel/lib/libwiringPi.so

.PHONY : test/CMakeFiles/wiringPi.dir/build

test/CMakeFiles/wiringPi.dir/clean:
	cd /home/ubuntu/catkin_ws/build/test && $(CMAKE_COMMAND) -P CMakeFiles/wiringPi.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/wiringPi.dir/clean

test/CMakeFiles/wiringPi.dir/depend:
	cd /home/ubuntu/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/catkin_ws/src /home/ubuntu/catkin_ws/src/test /home/ubuntu/catkin_ws/build /home/ubuntu/catkin_ws/build/test /home/ubuntu/catkin_ws/build/test/CMakeFiles/wiringPi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/wiringPi.dir/depend

