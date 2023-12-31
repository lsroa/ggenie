# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/luis.roa/Developer/ggenie

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/luis.roa/Developer/ggenie

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/opt/homebrew/Cellar/cmake/3.27.6/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/opt/homebrew/Cellar/cmake/3.27.6/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/luis.roa/Developer/ggenie/CMakeFiles /Users/luis.roa/Developer/ggenie//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/luis.roa/Developer/ggenie/CMakeFiles 0
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
# Target rules for targets named engine

# Build rule for target.
engine: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 engine
.PHONY : engine

# fast build rule for target.
engine/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/build
.PHONY : engine/fast

src/AssetStore/asset_store.o: src/AssetStore/asset_store.cpp.o
.PHONY : src/AssetStore/asset_store.o

# target to build an object file
src/AssetStore/asset_store.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/AssetStore/asset_store.cpp.o
.PHONY : src/AssetStore/asset_store.cpp.o

src/AssetStore/asset_store.i: src/AssetStore/asset_store.cpp.i
.PHONY : src/AssetStore/asset_store.i

# target to preprocess a source file
src/AssetStore/asset_store.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/AssetStore/asset_store.cpp.i
.PHONY : src/AssetStore/asset_store.cpp.i

src/AssetStore/asset_store.s: src/AssetStore/asset_store.cpp.s
.PHONY : src/AssetStore/asset_store.s

# target to generate assembly for a file
src/AssetStore/asset_store.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/AssetStore/asset_store.cpp.s
.PHONY : src/AssetStore/asset_store.cpp.s

src/ECS/ecs.o: src/ECS/ecs.cpp.o
.PHONY : src/ECS/ecs.o

# target to build an object file
src/ECS/ecs.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/ECS/ecs.cpp.o
.PHONY : src/ECS/ecs.cpp.o

src/ECS/ecs.i: src/ECS/ecs.cpp.i
.PHONY : src/ECS/ecs.i

# target to preprocess a source file
src/ECS/ecs.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/ECS/ecs.cpp.i
.PHONY : src/ECS/ecs.cpp.i

src/ECS/ecs.s: src/ECS/ecs.cpp.s
.PHONY : src/ECS/ecs.s

# target to generate assembly for a file
src/ECS/ecs.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/ECS/ecs.cpp.s
.PHONY : src/ECS/ecs.cpp.s

src/Game/game.o: src/Game/game.cpp.o
.PHONY : src/Game/game.o

# target to build an object file
src/Game/game.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/Game/game.cpp.o
.PHONY : src/Game/game.cpp.o

src/Game/game.i: src/Game/game.cpp.i
.PHONY : src/Game/game.i

# target to preprocess a source file
src/Game/game.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/Game/game.cpp.i
.PHONY : src/Game/game.cpp.i

src/Game/game.s: src/Game/game.cpp.s
.PHONY : src/Game/game.s

# target to generate assembly for a file
src/Game/game.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/Game/game.cpp.s
.PHONY : src/Game/game.cpp.s

src/Logger/logger.o: src/Logger/logger.cpp.o
.PHONY : src/Logger/logger.o

# target to build an object file
src/Logger/logger.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/Logger/logger.cpp.o
.PHONY : src/Logger/logger.cpp.o

src/Logger/logger.i: src/Logger/logger.cpp.i
.PHONY : src/Logger/logger.i

# target to preprocess a source file
src/Logger/logger.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/Logger/logger.cpp.i
.PHONY : src/Logger/logger.cpp.i

src/Logger/logger.s: src/Logger/logger.cpp.s
.PHONY : src/Logger/logger.s

# target to generate assembly for a file
src/Logger/logger.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/Logger/logger.cpp.s
.PHONY : src/Logger/logger.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... engine"
	@echo "... src/AssetStore/asset_store.o"
	@echo "... src/AssetStore/asset_store.i"
	@echo "... src/AssetStore/asset_store.s"
	@echo "... src/ECS/ecs.o"
	@echo "... src/ECS/ecs.i"
	@echo "... src/ECS/ecs.s"
	@echo "... src/Game/game.o"
	@echo "... src/Game/game.i"
	@echo "... src/Game/game.s"
	@echo "... src/Logger/logger.o"
	@echo "... src/Logger/logger.i"
	@echo "... src/Logger/logger.s"
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

