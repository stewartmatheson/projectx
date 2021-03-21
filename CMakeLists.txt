cmake_minimum_required(VERSION 3.10)

project(ProjectX VERSION 1.0)

link_directories(/usr/lib/debug/usr/lib)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(
	ProjectX 
	headers/Tile.h
	headers/Editor.h
	src/Tile.cpp 
	src/Editor.cpp 
	src/main.cpp 
	)
target_link_libraries(ProjectX sfml-graphics sfml-window sfml-system)
target_include_directories(ProjectX PRIVATE headers)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")
