#include "HouseSceneReducer.h"

void HouseSceneReducer::AddTile(int x, int y) {
    auto state = GetState();
    auto tile = MapTile { 
        x,
        y,
        state.selected_tile_rotation,
        state.selected_tile_index
    };
}

void HouseSceneReducer::AddEntity(int x, int y) {
    auto state = GetState();
    auto entity = Entity(selected_tile.entity_type, 0, 0, x, y)
}

void HouseSceneReducer::MoveTilePaletteView(int x, int y) {
    state.tile_palette_view.move(x, y);
}

void HouseSceneReducer::MoveHouseView(int x, int y) {
    state.house_view.move(x, y);
}

void HouseSceneReducer::MoveHouseView(int x, int y) {
    state.house_view.setSize(x, y);
}
