#include "HouseSceneReducer.h"

HouseSceneReducer::HouseSceneReducer(HouseSceneState& state) : state(state) {}

const HouseSceneState& HouseSceneReducer::GetState()  { return state; }

void HouseSceneReducer::MoveTilePaletteView(int x, int y) {
    state.editor_state.tile_palette_view.move(x, y);
}

void HouseSceneReducer::MoveHouseView(int x, int y) {
    state.house_view.move(x, y);
}

void HouseSceneReducer::AddTileLayer(TileLayer tile_layer) {
    state.tile_layers.push_back(tile_layer);
}

void HouseSceneReducer::AddTile(int x, int y) {
    auto state = GetState();
    auto tile = MapTile { 
        x,
        y,
        state.editor_state.selected_tile_rotation,
        state.editor_state.selected_tile_index
    };

    if (state.tile_layers.size() == 0) {
        state.tile_layers.push_back(TileLayer{0, std::vector<MapTile>()});
    }

    state.tile_layers[0].tiles.push_back(tile);
}

void HouseSceneReducer::AddEntity(int x, int y) {
    auto state = GetState();
    auto entity_type = state
        .editor_state
        .tile_palette_tiles[state.editor_state.selected_tile_index]
        .entity_type;
    
    std::unordered_map<EntityState, Animation> animations = {};
    auto entity = Entity(entity_type, 0, 0, x, y, animations);
    state.entities.push_back(entity);
}

void HouseSceneReducer::AddEntity(Entity entity) {
    state.entities.push_back(entity);
}

void HouseSceneReducer::SetPanning(bool new_panning_value) {
    state.editor_state.panning = new_panning_value; 
}

void HouseSceneReducer::SetRotation(int new_selected_rotation) {
    state.editor_state.selected_tile_rotation = new_selected_rotation; 
}

void HouseSceneReducer::UpdateSelectedTileIndex(int new_index) {
    state.editor_state.selected_tile_index = new_index; 
}

void HouseSceneReducer::ToggleEditorEnabled() {
    state.editor_state.editor_enabled = !state.editor_state.editor_enabled;
}

void HouseSceneReducer::SetMapBounds(sf::IntRect new_map_bounds) {
    state.map_bounds = new_map_bounds;
}

void HouseSceneReducer::ResetPlayer() {
    auto found_player = std::find_if(
        state.entities.begin(), 
        state.entities.end(),
        [](const auto &entity) { return entity.GetEntityType() == EntityType::PlayerEntity; }
    );

    if (found_player != state.entities.end()) {
        found_player->SetVelocity(sf::Vector2f(0,0));
    }
}

void HouseSceneReducer::AddTilePaletteTile(TilePaletteTile tile_to_add, int sprite_size) {
    auto offset = 20;
    auto current_tile_index = state.editor_state.tile_palette_tiles.size();
    auto y = (current_tile_index * sprite_size) + (offset * current_tile_index) + offset;
    tile_to_add.icon.setPosition(offset, y);
    state.editor_state.tile_palette_tiles.push_back(tile_to_add);
}

