# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /home/marcosmartinez/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/marcosmartinez/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/shell.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/shell.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/shell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shell.dir/flags.make

CMakeFiles/shell.dir/main.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/main.c.o: /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/main.c
CMakeFiles/shell.dir/main.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/shell.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/main.c.o -MF CMakeFiles/shell.dir/main.c.o.d -o CMakeFiles/shell.dir/main.c.o -c /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/main.c

CMakeFiles/shell.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/shell.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/main.c > CMakeFiles/shell.dir/main.c.i

CMakeFiles/shell.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/shell.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/main.c -o CMakeFiles/shell.dir/main.c.s

CMakeFiles/shell.dir/shell.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/shell.c.o: /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/shell.c
CMakeFiles/shell.dir/shell.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/shell.dir/shell.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/shell.c.o -MF CMakeFiles/shell.dir/shell.c.o.d -o CMakeFiles/shell.dir/shell.c.o -c /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/shell.c

CMakeFiles/shell.dir/shell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/shell.dir/shell.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/shell.c > CMakeFiles/shell.dir/shell.c.i

CMakeFiles/shell.dir/shell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/shell.dir/shell.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/shell.c -o CMakeFiles/shell.dir/shell.c.s

CMakeFiles/shell.dir/infPipes.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/infPipes.c.o: /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/infPipes.c
CMakeFiles/shell.dir/infPipes.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/shell.dir/infPipes.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/infPipes.c.o -MF CMakeFiles/shell.dir/infPipes.c.o.d -o CMakeFiles/shell.dir/infPipes.c.o -c /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/infPipes.c

CMakeFiles/shell.dir/infPipes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/shell.dir/infPipes.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/infPipes.c > CMakeFiles/shell.dir/infPipes.c.i

CMakeFiles/shell.dir/infPipes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/shell.dir/infPipes.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/infPipes.c -o CMakeFiles/shell.dir/infPipes.c.s

# Object files for target shell
shell_OBJECTS = \
"CMakeFiles/shell.dir/main.c.o" \
"CMakeFiles/shell.dir/shell.c.o" \
"CMakeFiles/shell.dir/infPipes.c.o"

# External object files for target shell
shell_EXTERNAL_OBJECTS =

shell: CMakeFiles/shell.dir/main.c.o
shell: CMakeFiles/shell.dir/shell.c.o
shell: CMakeFiles/shell.dir/infPipes.c.o
shell: CMakeFiles/shell.dir/build.make
shell: CMakeFiles/shell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable shell"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shell.dir/build: shell
.PHONY : CMakeFiles/shell.dir/build

CMakeFiles/shell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shell.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shell.dir/clean

CMakeFiles/shell.dir/depend:
	cd /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/cmake-build-debug /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/cmake-build-debug /home/marcosmartinez/Semestre_IV/sistemasOperativos/shell/cmake-build-debug/CMakeFiles/shell.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/shell.dir/depend

