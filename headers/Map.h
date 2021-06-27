#pragma once

#include "HouseSceneReducer.h"
#include <SFML/Graphics.hpp>

// A map holds all data for a given tile layout within the game.
class Map {
    HouseSceneReducer &reducer;

  public:
    Map(HouseSceneReducer &);
    Map(HouseSceneReducer &, std::string);
    void WriteToFile(std::string) const;
};
