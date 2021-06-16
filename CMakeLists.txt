cmake_minimum_required(VERSION 3.10)

project(ProjectX VERSION 1.0)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ProjectX
  headers/HouseSceneReducer.h
  headers/TileLayer.h
  headers/Animation.h
  headers/Tile.h
  headers/HouseScene.h
  headers/Map.h
  headers/SpriteSheet.h
  headers/Entity.h
  headers/TilePaletteView.h
  headers/TilePaletteTile.h
  headers/Controller.h
  headers/EditorController.h
  headers/PlayerController.h
  headers/View.h
  headers/EventWithMouse.h
  headers/HouseSceneState.h
  headers/EntityView.h
  headers/GridView.h
  headers/TileBackgroundView.h
  headers/ViewLayer.h
  headers/SelectedTileView.h
  headers/BoxSelectionView.h
  headers/GridSelectionView.h
  src/Animation.cpp
  src/HouseScene.cpp
  src/Map.cpp
  src/SpriteSheet.cpp
  src/Entity.cpp
  src/main.cpp
  src/TilePaletteView.cpp
  src/EditorController.cpp
  src/PlayerController.cpp
  src/HouseSceneReducer.cpp
  src/EntityView.cpp
  src/GridView.cpp
  src/TileBackgroundView.cpp
  src/ViewLayer.cpp
  src/SelectedTileView.cpp
  src/BoxSelectionView.cpp
  src/GridSelectionView.cpp
)

target_include_directories(ProjectX
  PRIVATE headers
)
target_link_directories(ProjectX
  PRIVATE /usr/lib/debug/usr/lib
)
target_link_libraries(ProjectX
  sfml-graphics-d
  sfml-system-d
  sfml-window-d
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
