# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /Users/macbook2015/Desktop/brew/bin/cmake

# The command to remove a file.
RM = /Users/macbook2015/Desktop/brew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp

# Include any dependencies generated for this target.
include ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/compiler_depend.make

# Include the progress variables for this target.
include ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/progress.make

# Include the compile flags for this target's objects.
include ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/flags.make

ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/codegen:
.PHONY : ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/codegen

ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/ggml-blas.cpp.o: ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/flags.make
ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/ggml-blas.cpp.o: ggml/src/ggml-blas/ggml-blas.cpp
ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/ggml-blas.cpp.o: ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/macbook2015/Documents/GitHub/stable-diffusion.cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/ggml-blas.cpp.o"
	cd /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp/ggml/src/ggml-blas && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/ggml-blas.cpp.o -MF CMakeFiles/ggml-blas.dir/ggml-blas.cpp.o.d -o CMakeFiles/ggml-blas.dir/ggml-blas.cpp.o -c /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp/ggml/src/ggml-blas/ggml-blas.cpp

ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/ggml-blas.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ggml-blas.dir/ggml-blas.cpp.i"
	cd /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp/ggml/src/ggml-blas && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp/ggml/src/ggml-blas/ggml-blas.cpp > CMakeFiles/ggml-blas.dir/ggml-blas.cpp.i

ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/ggml-blas.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ggml-blas.dir/ggml-blas.cpp.s"
	cd /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp/ggml/src/ggml-blas && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp/ggml/src/ggml-blas/ggml-blas.cpp -o CMakeFiles/ggml-blas.dir/ggml-blas.cpp.s

# Object files for target ggml-blas
ggml__blas_OBJECTS = \
"CMakeFiles/ggml-blas.dir/ggml-blas.cpp.o"

# External object files for target ggml-blas
ggml__blas_EXTERNAL_OBJECTS =

ggml/src/ggml-blas/libggml-blas.a: ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/ggml-blas.cpp.o
ggml/src/ggml-blas/libggml-blas.a: ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/build.make
ggml/src/ggml-blas/libggml-blas.a: ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/macbook2015/Documents/GitHub/stable-diffusion.cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libggml-blas.a"
	cd /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp/ggml/src/ggml-blas && $(CMAKE_COMMAND) -P CMakeFiles/ggml-blas.dir/cmake_clean_target.cmake
	cd /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp/ggml/src/ggml-blas && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ggml-blas.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/build: ggml/src/ggml-blas/libggml-blas.a
.PHONY : ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/build

ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/clean:
	cd /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp/ggml/src/ggml-blas && $(CMAKE_COMMAND) -P CMakeFiles/ggml-blas.dir/cmake_clean.cmake
.PHONY : ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/clean

ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/depend:
	cd /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp/ggml/src/ggml-blas /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp/ggml/src/ggml-blas /Users/macbook2015/Documents/GitHub/stable-diffusion.cpp/ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : ggml/src/ggml-blas/CMakeFiles/ggml-blas.dir/depend

