# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\msys64\mingw64\bin\cmake.exe

# The command to remove a file.
RM = C:\msys64\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\keyli\Documents\IUT\R3_02_Cpp\TP\TP4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\keyli\Documents\IUT\R3_02_Cpp\TP\TP4

# Utility rule file for main_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/main_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main_autogen.dir/progress.make

CMakeFiles/main_autogen: main_autogen/timestamp

main_autogen/timestamp: C:/Qt/6.8.0/mingw_64/bin/moc.exe
main_autogen/timestamp: CMakeFiles/main_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:\Users\keyli\Documents\IUT\R3_02_Cpp\TP\TP4\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target main"
	C:\msys64\mingw64\bin\cmake.exe -E cmake_autogen C:/Users/keyli/Documents/IUT/R3_02_Cpp/TP/TP4/CMakeFiles/main_autogen.dir/AutogenInfo.json ""
	C:\msys64\mingw64\bin\cmake.exe -E touch C:/Users/keyli/Documents/IUT/R3_02_Cpp/TP/TP4/main_autogen/timestamp

CMakeFiles/main_autogen.dir/codegen:
.PHONY : CMakeFiles/main_autogen.dir/codegen

main_autogen: CMakeFiles/main_autogen
main_autogen: main_autogen/timestamp
main_autogen: CMakeFiles/main_autogen.dir/build.make
.PHONY : main_autogen

# Rule to build all files generated by this target.
CMakeFiles/main_autogen.dir/build: main_autogen
.PHONY : CMakeFiles/main_autogen.dir/build

CMakeFiles/main_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\main_autogen.dir\cmake_clean.cmake
.PHONY : CMakeFiles/main_autogen.dir/clean

CMakeFiles/main_autogen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\keyli\Documents\IUT\R3_02_Cpp\TP\TP4 C:\Users\keyli\Documents\IUT\R3_02_Cpp\TP\TP4 C:\Users\keyli\Documents\IUT\R3_02_Cpp\TP\TP4 C:\Users\keyli\Documents\IUT\R3_02_Cpp\TP\TP4 C:\Users\keyli\Documents\IUT\R3_02_Cpp\TP\TP4\CMakeFiles\main_autogen.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/main_autogen.dir/depend

