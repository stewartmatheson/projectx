#pragma once

#include "Entity.h"
#include "HouseSceneState.h"

class HouseSceneReducer {
    HouseSceneState& state;
public:
    HouseSceneReducer(HouseSceneState&);
    const HouseSceneState& GetState();
    void ToggleEditorEnabled();
    void ResetPlayer();
    void UpdateSelectedTileIndex(int);
    void AddTileLayer(TileLayer);
    void AddEntity(Entity);
    void AddTile(int, int);
    void AddEntity(int, int);
    void SetPanning(bool);
    void SetMapBounds(sf::IntRect);
    void SetRotation(int);
    void SetTilePaletteBounds(int, int, int);
    void MoveTilePaletteView(int, int);
    void MoveHouseView(int, int);
    void HouseViewSetSize(int, int);
    void AddTilePaletteTile(TilePaletteTile, int);
    void InitSelectionRectangle(int);
    void SetSelectionRectanglePosition(sf::Vector2f);
    void UpdateSelectedEditorSquare(sf::Vector2i);
    void SetHouseViewCenter(sf::Vector2f);
    void SetEntityTransform(sf::Vector2f);
    void SetEntityVelocity(sf::Vector2f);
    void MousePressedAt();
    void MouseReleased(sf::Vector2f, int);
    void UpdateMousePosition(sf::Vector2f);
};
