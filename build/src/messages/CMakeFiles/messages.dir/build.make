# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/axu/projects/TcpServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/axu/projects/TcpServer/build

# Include any dependencies generated for this target.
include src/messages/CMakeFiles/messages.dir/depend.make

# Include the progress variables for this target.
include src/messages/CMakeFiles/messages.dir/progress.make

# Include the compile flags for this target's objects.
include src/messages/CMakeFiles/messages.dir/flags.make

src/messages/CMakeFiles/messages.dir/info_remote_handler.c.o: src/messages/CMakeFiles/messages.dir/flags.make
src/messages/CMakeFiles/messages.dir/info_remote_handler.c.o: ../src/messages/info_remote_handler.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/axu/projects/TcpServer/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/messages/CMakeFiles/messages.dir/info_remote_handler.c.o"
	cd /home/axu/projects/TcpServer/build/src/messages && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/messages.dir/info_remote_handler.c.o   -c /home/axu/projects/TcpServer/src/messages/info_remote_handler.c

src/messages/CMakeFiles/messages.dir/info_remote_handler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/messages.dir/info_remote_handler.c.i"
	cd /home/axu/projects/TcpServer/build/src/messages && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/axu/projects/TcpServer/src/messages/info_remote_handler.c > CMakeFiles/messages.dir/info_remote_handler.c.i

src/messages/CMakeFiles/messages.dir/info_remote_handler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/messages.dir/info_remote_handler.c.s"
	cd /home/axu/projects/TcpServer/build/src/messages && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/axu/projects/TcpServer/src/messages/info_remote_handler.c -o CMakeFiles/messages.dir/info_remote_handler.c.s

src/messages/CMakeFiles/messages.dir/info_remote_handler.c.o.requires:
.PHONY : src/messages/CMakeFiles/messages.dir/info_remote_handler.c.o.requires

src/messages/CMakeFiles/messages.dir/info_remote_handler.c.o.provides: src/messages/CMakeFiles/messages.dir/info_remote_handler.c.o.requires
	$(MAKE) -f src/messages/CMakeFiles/messages.dir/build.make src/messages/CMakeFiles/messages.dir/info_remote_handler.c.o.provides.build
.PHONY : src/messages/CMakeFiles/messages.dir/info_remote_handler.c.o.provides

src/messages/CMakeFiles/messages.dir/info_remote_handler.c.o.provides.build: src/messages/CMakeFiles/messages.dir/info_remote_handler.c.o

src/messages/CMakeFiles/messages.dir/info_local_handler.c.o: src/messages/CMakeFiles/messages.dir/flags.make
src/messages/CMakeFiles/messages.dir/info_local_handler.c.o: ../src/messages/info_local_handler.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/axu/projects/TcpServer/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/messages/CMakeFiles/messages.dir/info_local_handler.c.o"
	cd /home/axu/projects/TcpServer/build/src/messages && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/messages.dir/info_local_handler.c.o   -c /home/axu/projects/TcpServer/src/messages/info_local_handler.c

src/messages/CMakeFiles/messages.dir/info_local_handler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/messages.dir/info_local_handler.c.i"
	cd /home/axu/projects/TcpServer/build/src/messages && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/axu/projects/TcpServer/src/messages/info_local_handler.c > CMakeFiles/messages.dir/info_local_handler.c.i

src/messages/CMakeFiles/messages.dir/info_local_handler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/messages.dir/info_local_handler.c.s"
	cd /home/axu/projects/TcpServer/build/src/messages && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/axu/projects/TcpServer/src/messages/info_local_handler.c -o CMakeFiles/messages.dir/info_local_handler.c.s

src/messages/CMakeFiles/messages.dir/info_local_handler.c.o.requires:
.PHONY : src/messages/CMakeFiles/messages.dir/info_local_handler.c.o.requires

src/messages/CMakeFiles/messages.dir/info_local_handler.c.o.provides: src/messages/CMakeFiles/messages.dir/info_local_handler.c.o.requires
	$(MAKE) -f src/messages/CMakeFiles/messages.dir/build.make src/messages/CMakeFiles/messages.dir/info_local_handler.c.o.provides.build
.PHONY : src/messages/CMakeFiles/messages.dir/info_local_handler.c.o.provides

src/messages/CMakeFiles/messages.dir/info_local_handler.c.o.provides.build: src/messages/CMakeFiles/messages.dir/info_local_handler.c.o

# Object files for target messages
messages_OBJECTS = \
"CMakeFiles/messages.dir/info_remote_handler.c.o" \
"CMakeFiles/messages.dir/info_local_handler.c.o"

# External object files for target messages
messages_EXTERNAL_OBJECTS =

src/messages/libmessages.a: src/messages/CMakeFiles/messages.dir/info_remote_handler.c.o
src/messages/libmessages.a: src/messages/CMakeFiles/messages.dir/info_local_handler.c.o
src/messages/libmessages.a: src/messages/CMakeFiles/messages.dir/build.make
src/messages/libmessages.a: src/messages/CMakeFiles/messages.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libmessages.a"
	cd /home/axu/projects/TcpServer/build/src/messages && $(CMAKE_COMMAND) -P CMakeFiles/messages.dir/cmake_clean_target.cmake
	cd /home/axu/projects/TcpServer/build/src/messages && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/messages.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/messages/CMakeFiles/messages.dir/build: src/messages/libmessages.a
.PHONY : src/messages/CMakeFiles/messages.dir/build

src/messages/CMakeFiles/messages.dir/requires: src/messages/CMakeFiles/messages.dir/info_remote_handler.c.o.requires
src/messages/CMakeFiles/messages.dir/requires: src/messages/CMakeFiles/messages.dir/info_local_handler.c.o.requires
.PHONY : src/messages/CMakeFiles/messages.dir/requires

src/messages/CMakeFiles/messages.dir/clean:
	cd /home/axu/projects/TcpServer/build/src/messages && $(CMAKE_COMMAND) -P CMakeFiles/messages.dir/cmake_clean.cmake
.PHONY : src/messages/CMakeFiles/messages.dir/clean

src/messages/CMakeFiles/messages.dir/depend:
	cd /home/axu/projects/TcpServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/axu/projects/TcpServer /home/axu/projects/TcpServer/src/messages /home/axu/projects/TcpServer/build /home/axu/projects/TcpServer/build/src/messages /home/axu/projects/TcpServer/build/src/messages/CMakeFiles/messages.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/messages/CMakeFiles/messages.dir/depend

