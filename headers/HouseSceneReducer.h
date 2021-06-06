#pragma once

#include "Entity.h"
#include "HouseSceneState.h"

class HouseSceneReducer {
    HouseSceneState& state;
public:
    HouseSceneReducer(HouseSceneState& state);
    const HouseSceneState& GetState();
    void ToggleEditorEnabled();
    void ResetPlayer();
    void UpdateSelectedTileIndex(const int index);
    void AddTileLayer(TileLayer tile_layer);
    void AddEntity(Entity entity);
    void AddTile(int x, int y);
    void AddEntity(int x, int y);
    void AddPlayer();
    void SetPanning(bool panning_mode);
    void SetMapBounds(sf::IntRect map_bounds);
    void SetRotation(int rotation);
    void MoveTilePaletteView(int x, int y);
    void MoveHouseView(int x, int y);
    void HouseViewSetSize(int x, int y);
};
