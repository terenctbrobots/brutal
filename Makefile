# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_SOURCE_DIR = /home/terenctb/Project/bigbadrobots/brutal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/terenctb/Project/bigbadrobots/brutal

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/terenctb/Project/bigbadrobots/brutal/CMakeFiles /home/terenctb/Project/bigbadrobots/brutal//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/terenctb/Project/bigbadrobots/brutal/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named brutal

# Build rule for target.
brutal: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 brutal
.PHONY : brutal

# fast build rule for target.
brutal/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/brutal.dir/build.make CMakeFiles/brutal.dir/build
.PHONY : brutal/fast

#=============================================================================
# Target rules for targets named copy_assets

# Build rule for target.
copy_assets: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 copy_assets
.PHONY : copy_assets

# fast build rule for target.
copy_assets/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/copy_assets.dir/build.make CMakeFiles/copy_assets.dir/build
.PHONY : copy_assets/fast

src/graphics/layer.o: src/graphics/layer.cpp.o
.PHONY : src/graphics/layer.o

# target to build an object file
src/graphics/layer.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/brutal.dir/build.make CMakeFiles/brutal.dir/src/graphics/layer.cpp.o
.PHONY : src/graphics/layer.cpp.o

src/graphics/layer.i: src/graphics/layer.cpp.i
.PHONY : src/graphics/layer.i

# target to preprocess a source file
src/graphics/layer.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/brutal.dir/build.make CMakeFiles/brutal.dir/src/graphics/layer.cpp.i
.PHONY : src/graphics/layer.cpp.i

src/graphics/layer.s: src/graphics/layer.cpp.s
.PHONY : src/graphics/layer.s

# target to generate assembly for a file
src/graphics/layer.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/brutal.dir/build.make CMakeFiles/brutal.dir/src/graphics/layer.cpp.s
.PHONY : src/graphics/layer.cpp.s

src/graphics/sprite.o: src/graphics/sprite.cpp.o
.PHONY : src/graphics/sprite.o

# target to build an object file
src/graphics/sprite.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/brutal.dir/build.make CMakeFiles/brutal.dir/src/graphics/sprite.cpp.o
.PHONY : src/graphics/sprite.cpp.o

src/graphics/sprite.i: src/graphics/sprite.cpp.i
.PHONY : src/graphics/sprite.i

# target to preprocess a source file
src/graphics/sprite.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/brutal.dir/build.make CMakeFiles/brutal.dir/src/graphics/sprite.cpp.i
.PHONY : src/graphics/sprite.cpp.i

src/graphics/sprite.s: src/graphics/sprite.cpp.s
.PHONY : src/graphics/sprite.s

# target to generate assembly for a file
src/graphics/sprite.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/brutal.dir/build.make CMakeFiles/brutal.dir/src/graphics/sprite.cpp.s
.PHONY : src/graphics/sprite.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/brutal.dir/build.make CMakeFiles/brutal.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/brutal.dir/build.make CMakeFiles/brutal.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/brutal.dir/build.make CMakeFiles/brutal.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... copy_assets"
	@echo "... brutal"
	@echo "... src/graphics/layer.o"
	@echo "... src/graphics/layer.i"
	@echo "... src/graphics/layer.s"
	@echo "... src/graphics/sprite.o"
	@echo "... src/graphics/sprite.i"
	@echo "... src/graphics/sprite.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

