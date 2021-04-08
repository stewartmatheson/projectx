cmake_minimum_required(VERSION 3.10)

project(ProjectX VERSION 1.0)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ProjectX
  headers/Editor.h
  headers/Room.h
  headers/TileMap.h
  src/Editor.cpp
  src/Room.cpp
  src/TileMap.cpp
  src/main.cpp
)
target_include_directories(ProjectX
  PRIVATE headers
)
target_link_directories(ProjectX
  PRIVATE /usr/lib/debug/usr/lib
)
target_link_libraries(ProjectX
  sfml-graphics
  sfml-system
  sfml-window
)
