# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/katanamanjaro/Documents/AP/cartesian-plotter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/katanamanjaro/Documents/AP/cartesian-plotter/Build

# Include any dependencies generated for this target.
include CMakeFiles/cartesian-plotter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cartesian-plotter.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cartesian-plotter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cartesian-plotter.dir/flags.make

CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.gch: CMakeFiles/cartesian-plotter.dir/flags.make
CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.gch: CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.cxx
CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.gch: CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx
CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.gch: CMakeFiles/cartesian-plotter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.gch"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx -MD -MT CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.gch -MF CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.gch.d -o CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.gch -c /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.cxx

CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx -E /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.cxx > CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.i

CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx -S /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.cxx -o CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.s

CMakeFiles/cartesian-plotter.dir/Main.cpp.o: CMakeFiles/cartesian-plotter.dir/flags.make
CMakeFiles/cartesian-plotter.dir/Main.cpp.o: ../Main.cpp
CMakeFiles/cartesian-plotter.dir/Main.cpp.o: CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx
CMakeFiles/cartesian-plotter.dir/Main.cpp.o: CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.gch
CMakeFiles/cartesian-plotter.dir/Main.cpp.o: CMakeFiles/cartesian-plotter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cartesian-plotter.dir/Main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx -MD -MT CMakeFiles/cartesian-plotter.dir/Main.cpp.o -MF CMakeFiles/cartesian-plotter.dir/Main.cpp.o.d -o CMakeFiles/cartesian-plotter.dir/Main.cpp.o -c /home/katanamanjaro/Documents/AP/cartesian-plotter/Main.cpp

CMakeFiles/cartesian-plotter.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cartesian-plotter.dir/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx -E /home/katanamanjaro/Documents/AP/cartesian-plotter/Main.cpp > CMakeFiles/cartesian-plotter.dir/Main.cpp.i

CMakeFiles/cartesian-plotter.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cartesian-plotter.dir/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx -S /home/katanamanjaro/Documents/AP/cartesian-plotter/Main.cpp -o CMakeFiles/cartesian-plotter.dir/Main.cpp.s

CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.o: CMakeFiles/cartesian-plotter.dir/flags.make
CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.o: ../Source/Core/Application.cpp
CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.o: CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx
CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.o: CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.gch
CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.o: CMakeFiles/cartesian-plotter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx -MD -MT CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.o -MF CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.o.d -o CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.o -c /home/katanamanjaro/Documents/AP/cartesian-plotter/Source/Core/Application.cpp

CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx -E /home/katanamanjaro/Documents/AP/cartesian-plotter/Source/Core/Application.cpp > CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.i

CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx -S /home/katanamanjaro/Documents/AP/cartesian-plotter/Source/Core/Application.cpp -o CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.s

CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.o: CMakeFiles/cartesian-plotter.dir/flags.make
CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.o: ../Source/Core/Window.cpp
CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.o: CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx
CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.o: CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.gch
CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.o: CMakeFiles/cartesian-plotter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx -MD -MT CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.o -MF CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.o.d -o CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.o -c /home/katanamanjaro/Documents/AP/cartesian-plotter/Source/Core/Window.cpp

CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx -E /home/katanamanjaro/Documents/AP/cartesian-plotter/Source/Core/Window.cpp > CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.i

CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx -S /home/katanamanjaro/Documents/AP/cartesian-plotter/Source/Core/Window.cpp -o CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.s

# Object files for target cartesian-plotter
cartesian__plotter_OBJECTS = \
"CMakeFiles/cartesian-plotter.dir/Main.cpp.o" \
"CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.o" \
"CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.o"

# External object files for target cartesian-plotter
cartesian__plotter_EXTERNAL_OBJECTS =

cartesian-plotter: CMakeFiles/cartesian-plotter.dir/cmake_pch.hxx.gch
cartesian-plotter: CMakeFiles/cartesian-plotter.dir/Main.cpp.o
cartesian-plotter: CMakeFiles/cartesian-plotter.dir/Source/Core/Application.cpp.o
cartesian-plotter: CMakeFiles/cartesian-plotter.dir/Source/Core/Window.cpp.o
cartesian-plotter: CMakeFiles/cartesian-plotter.dir/build.make
cartesian-plotter: External/libIMGUI.a
cartesian-plotter: External/glfw/src/libglfw3.a
cartesian-plotter: /usr/lib/libGLEW.so
cartesian-plotter: /usr/lib/librt.a
cartesian-plotter: /usr/lib/libm.so
cartesian-plotter: CMakeFiles/cartesian-plotter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable cartesian-plotter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cartesian-plotter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cartesian-plotter.dir/build: cartesian-plotter
.PHONY : CMakeFiles/cartesian-plotter.dir/build

CMakeFiles/cartesian-plotter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cartesian-plotter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cartesian-plotter.dir/clean

CMakeFiles/cartesian-plotter.dir/depend:
	cd /home/katanamanjaro/Documents/AP/cartesian-plotter/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/katanamanjaro/Documents/AP/cartesian-plotter /home/katanamanjaro/Documents/AP/cartesian-plotter /home/katanamanjaro/Documents/AP/cartesian-plotter/Build /home/katanamanjaro/Documents/AP/cartesian-plotter/Build /home/katanamanjaro/Documents/AP/cartesian-plotter/Build/CMakeFiles/cartesian-plotter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cartesian-plotter.dir/depend

