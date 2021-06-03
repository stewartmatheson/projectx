#pragma once

#include "HouseScene.h"
#include "Entity.h"

class HouseSceneReducer {
    HouseSceneState& state;
public:
    HouseSceneReducer(HouseSceneState& state);
    const HouseSceneState& GetState();
    void ToggleEditorEnabled();
    void ResetPlayer();
    void UpdateSelectedTileIndex(const int index);
    void AddTile(int x, int y);
    void AddEntity(int x, int y);
    void LoadMap();
    void AddPlayer();
    void SetPanning(bool panning_mode);
    void SetRotation(int rotation);
    void MoveTilePaletteView(int x, int y);
    void MoveHouseView(int x, int y);
    void HouseViewSetSize(int x, int y);
};
