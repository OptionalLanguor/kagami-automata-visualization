# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aluno/Kagami/kagami-automata-visualization

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aluno/Kagami/kagami-automata-visualization

# Include any dependencies generated for this target.
include CMakeFiles/Kagami.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Kagami.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Kagami.dir/flags.make

CMakeFiles/Kagami.dir/main.cpp.o: CMakeFiles/Kagami.dir/flags.make
CMakeFiles/Kagami.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aluno/Kagami/kagami-automata-visualization/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Kagami.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Kagami.dir/main.cpp.o -c /home/aluno/Kagami/kagami-automata-visualization/main.cpp

CMakeFiles/Kagami.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Kagami.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aluno/Kagami/kagami-automata-visualization/main.cpp > CMakeFiles/Kagami.dir/main.cpp.i

CMakeFiles/Kagami.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Kagami.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aluno/Kagami/kagami-automata-visualization/main.cpp -o CMakeFiles/Kagami.dir/main.cpp.s

CMakeFiles/Kagami.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Kagami.dir/main.cpp.o.requires

CMakeFiles/Kagami.dir/main.cpp.o.provides: CMakeFiles/Kagami.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Kagami.dir/build.make CMakeFiles/Kagami.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Kagami.dir/main.cpp.o.provides

CMakeFiles/Kagami.dir/main.cpp.o.provides.build: CMakeFiles/Kagami.dir/main.cpp.o


CMakeFiles/Kagami.dir/Entities/Entity.cpp.o: CMakeFiles/Kagami.dir/flags.make
CMakeFiles/Kagami.dir/Entities/Entity.cpp.o: Entities/Entity.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aluno/Kagami/kagami-automata-visualization/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Kagami.dir/Entities/Entity.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Kagami.dir/Entities/Entity.cpp.o -c /home/aluno/Kagami/kagami-automata-visualization/Entities/Entity.cpp

CMakeFiles/Kagami.dir/Entities/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Kagami.dir/Entities/Entity.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aluno/Kagami/kagami-automata-visualization/Entities/Entity.cpp > CMakeFiles/Kagami.dir/Entities/Entity.cpp.i

CMakeFiles/Kagami.dir/Entities/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Kagami.dir/Entities/Entity.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aluno/Kagami/kagami-automata-visualization/Entities/Entity.cpp -o CMakeFiles/Kagami.dir/Entities/Entity.cpp.s

CMakeFiles/Kagami.dir/Entities/Entity.cpp.o.requires:

.PHONY : CMakeFiles/Kagami.dir/Entities/Entity.cpp.o.requires

CMakeFiles/Kagami.dir/Entities/Entity.cpp.o.provides: CMakeFiles/Kagami.dir/Entities/Entity.cpp.o.requires
	$(MAKE) -f CMakeFiles/Kagami.dir/build.make CMakeFiles/Kagami.dir/Entities/Entity.cpp.o.provides.build
.PHONY : CMakeFiles/Kagami.dir/Entities/Entity.cpp.o.provides

CMakeFiles/Kagami.dir/Entities/Entity.cpp.o.provides.build: CMakeFiles/Kagami.dir/Entities/Entity.cpp.o


CMakeFiles/Kagami.dir/Entities/Component.cpp.o: CMakeFiles/Kagami.dir/flags.make
CMakeFiles/Kagami.dir/Entities/Component.cpp.o: Entities/Component.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aluno/Kagami/kagami-automata-visualization/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Kagami.dir/Entities/Component.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Kagami.dir/Entities/Component.cpp.o -c /home/aluno/Kagami/kagami-automata-visualization/Entities/Component.cpp

CMakeFiles/Kagami.dir/Entities/Component.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Kagami.dir/Entities/Component.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aluno/Kagami/kagami-automata-visualization/Entities/Component.cpp > CMakeFiles/Kagami.dir/Entities/Component.cpp.i

CMakeFiles/Kagami.dir/Entities/Component.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Kagami.dir/Entities/Component.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aluno/Kagami/kagami-automata-visualization/Entities/Component.cpp -o CMakeFiles/Kagami.dir/Entities/Component.cpp.s

CMakeFiles/Kagami.dir/Entities/Component.cpp.o.requires:

.PHONY : CMakeFiles/Kagami.dir/Entities/Component.cpp.o.requires

CMakeFiles/Kagami.dir/Entities/Component.cpp.o.provides: CMakeFiles/Kagami.dir/Entities/Component.cpp.o.requires
	$(MAKE) -f CMakeFiles/Kagami.dir/build.make CMakeFiles/Kagami.dir/Entities/Component.cpp.o.provides.build
.PHONY : CMakeFiles/Kagami.dir/Entities/Component.cpp.o.provides

CMakeFiles/Kagami.dir/Entities/Component.cpp.o.provides.build: CMakeFiles/Kagami.dir/Entities/Component.cpp.o


# Object files for target Kagami
Kagami_OBJECTS = \
"CMakeFiles/Kagami.dir/main.cpp.o" \
"CMakeFiles/Kagami.dir/Entities/Entity.cpp.o" \
"CMakeFiles/Kagami.dir/Entities/Component.cpp.o"

# External object files for target Kagami
Kagami_EXTERNAL_OBJECTS =

Kagami: CMakeFiles/Kagami.dir/main.cpp.o
Kagami: CMakeFiles/Kagami.dir/Entities/Entity.cpp.o
Kagami: CMakeFiles/Kagami.dir/Entities/Component.cpp.o
Kagami: CMakeFiles/Kagami.dir/build.make
Kagami: /usr/lib/x86_64-linux-gnu/libGLEW.so
Kagami: /usr/lib/x86_64-linux-gnu/libGLU.so
Kagami: /usr/lib/x86_64-linux-gnu/libGL.so
Kagami: /usr/lib/x86_64-linux-gnu/libGLEW.so
Kagami: external/glfw-3.1.2/src/libglfw3.a
Kagami: /usr/lib/x86_64-linux-gnu/librt.so
Kagami: /usr/lib/x86_64-linux-gnu/libm.so
Kagami: /usr/lib/x86_64-linux-gnu/libX11.so
Kagami: /usr/lib/x86_64-linux-gnu/libXrandr.so
Kagami: /usr/lib/x86_64-linux-gnu/libXinerama.so
Kagami: /usr/lib/x86_64-linux-gnu/libXi.so
Kagami: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
Kagami: /usr/lib/x86_64-linux-gnu/libXcursor.so
Kagami: /usr/lib/x86_64-linux-gnu/libGL.so
Kagami: /usr/lib/x86_64-linux-gnu/librt.so
Kagami: /usr/lib/x86_64-linux-gnu/libm.so
Kagami: /usr/lib/x86_64-linux-gnu/libX11.so
Kagami: /usr/lib/x86_64-linux-gnu/libXrandr.so
Kagami: /usr/lib/x86_64-linux-gnu/libXinerama.so
Kagami: /usr/lib/x86_64-linux-gnu/libXi.so
Kagami: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
Kagami: /usr/lib/x86_64-linux-gnu/libXcursor.so
Kagami: /usr/lib/x86_64-linux-gnu/libGLEW.so
Kagami: CMakeFiles/Kagami.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aluno/Kagami/kagami-automata-visualization/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Kagami"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Kagami.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Kagami.dir/build: Kagami

.PHONY : CMakeFiles/Kagami.dir/build

CMakeFiles/Kagami.dir/requires: CMakeFiles/Kagami.dir/main.cpp.o.requires
CMakeFiles/Kagami.dir/requires: CMakeFiles/Kagami.dir/Entities/Entity.cpp.o.requires
CMakeFiles/Kagami.dir/requires: CMakeFiles/Kagami.dir/Entities/Component.cpp.o.requires

.PHONY : CMakeFiles/Kagami.dir/requires

CMakeFiles/Kagami.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Kagami.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Kagami.dir/clean

CMakeFiles/Kagami.dir/depend:
	cd /home/aluno/Kagami/kagami-automata-visualization && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aluno/Kagami/kagami-automata-visualization /home/aluno/Kagami/kagami-automata-visualization /home/aluno/Kagami/kagami-automata-visualization /home/aluno/Kagami/kagami-automata-visualization /home/aluno/Kagami/kagami-automata-visualization/CMakeFiles/Kagami.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Kagami.dir/depend

