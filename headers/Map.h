#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "HouseSceneReducer.h"

// A map holds all data for a given tile layout within the game.
class Map {
  public:
    static void WriteToFile(std::string, MapState);
    static MapState ReadFromFile(std::string);
    static MapState New();
    static int GetSpriteSize();
};
