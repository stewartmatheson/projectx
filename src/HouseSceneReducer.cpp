#include "HouseSceneReducer.h"

void HouseSceneReducer::MoveTilePaletteView(int x, int y) {
    state.editor_state.tile_palette_view.move(x, y);
}

void HouseSceneReducer::MoveHouseView(int x, int y) {
    state.house_view.move(x, y);
}


void HouseSceneReducer::AddTile(int x, int y) {
    auto state = GetState();
    auto tile = MapTile { 
        x,
        y,
        state.editor_state.selected_tile_rotation,
        state.editor_state.selected_tile_index
    };
    state.tile_layers[0].tiles.push_back(tile);
}


/*
void HouseSceneReducer::MoveHouseView(int x, int y) {
    state.house_view.setSize(x, y);
}
*/

void HouseSceneReducer::AddEntity(int x, int y) {
    auto state = GetState();
    auto entity_type = state
        .editor_state
        .tile_palette_tiles[state.editor_state.selected_tile_index]
        .entity_type;
    
    auto entity = Entity(entity_type, 0, 0, x, y);
    state.entities.push_back(entity);
}

void HouseSceneReducer::AddEntity(Entity entity) {
    state.entities.push_back(entity);
}

