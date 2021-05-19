cmake_minimum_required(VERSION 3.10)

project(ProjectX VERSION 1.0)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ProjectX
  headers/Animation.h
  headers/Tile.h
  headers/HouseScene.h
  headers/House.h
  headers/SpriteSheet.h
  headers/Entity.h
  headers/TilePaletteView.h
  headers/TilePaletteTile.h
  src/Animation.cpp
  src/HouseScene.cpp
  src/House.cpp
  src/SpriteSheet.cpp
  src/Entity.cpp
  src/main.cpp
  src/TilePaletteView.cpp
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

if(DEFINED SFML_PREFIX)
  target_include_directories(ProjectX
    PRIVATE ${SFML_PREFIX}/include
  )
  target_link_directories(ProjectX
    PRIVATE ${SFML_PREFIX}/lib
  )
endif()

if(DEFINED ENV{SFML_PREFIX})
  target_include_directories(ProjectX
    PRIVATE $ENV{SFML_PREFIX}/include
  )
  target_link_directories(ProjectX
    PRIVATE $ENV{SFML_PREFIX}/lib
  )
endif()
