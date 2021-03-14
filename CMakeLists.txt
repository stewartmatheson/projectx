cmake_minimum_required(VERSION 3.10)

project(ProjectX VERSION 1.0)

link_directories(/usr/lib/debug/usr/lib)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(ProjectX src/main.cpp)
target_link_libraries(ProjectX sfml-graphics sfml-window sfml-system)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")
