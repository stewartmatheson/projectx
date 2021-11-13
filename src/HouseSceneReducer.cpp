#include "HouseSceneReducer.h"
#include <math.h>

const HouseSceneState &HouseSceneReducer::GetState() { return state; }

void HouseSceneReducer::AddTileLayer(TileLayer tile_layer) {
    state.map.tile_layers.push_back(tile_layer);
}

void HouseSceneReducer::AddTile(int x, int y) {
    auto tile = MapTile{x, y, state.editor_state.selected_tile_rotation,
                        state.editor_state.selected_tile_index};

    if (state.map.tile_layers.size() == 0) {
        state.map.tile_layers.push_back(TileLayer{0, std::vector<MapTile>()});
    }

    state.map.tile_layers[0].tiles.push_back(tile);
}

void HouseSceneReducer::AddEntity(int x, int y) {
    auto entity_type =
        state.editor_state
            .tile_palette_tiles[state.editor_state.selected_tile_index]
            .entity_type;

    auto entity = Entity{entity_type, 0, 0, sf::Vector2f(x, y)};
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

void HouseSceneReducer::ResetPlayer() {
    auto found_player = std::find_if(
        state.entities.begin(), state.entities.end(), [](const auto &entity) {
            return entity.type == EntityType::PlayerEntity;
        });

    if (found_player != state.entities.end()) {
        found_player->velocity = sf::Vector2f(0, 0);
    }
}

void HouseSceneReducer::AddTilePaletteTile(TilePaletteTile tile_to_add,
                                           int sprite_size) {
    auto offset = 20;
    auto current_tile_index = state.editor_state.tile_palette_tiles.size();
    auto y = (current_tile_index * sprite_size) +
             (offset * current_tile_index) + offset;
    tile_to_add.icon.setPosition(offset, y);
    state.editor_state.tile_palette_tiles.push_back(tile_to_add);
}

void HouseSceneReducer::InitSelectionRectangle(int sprite_size) {
    state.editor_state.tile_palette_selection_rectangle.setSize(
        sf::Vector2f(sprite_size, sprite_size));
    state.editor_state.tile_palette_selection_rectangle.setOutlineColor(
        sf::Color::Blue);
    state.editor_state.tile_palette_selection_rectangle.setOutlineThickness(2);
    state.editor_state.tile_palette_selection_rectangle.setFillColor(
        sf::Color::Transparent);
}

void HouseSceneReducer::SetSelectionRectanglePosition(
    sf::Vector2f new_position) {
    state.editor_state.tile_palette_selection_rectangle.setPosition(
        new_position);
}

void HouseSceneReducer::UpdateSelectedEditorSquare(
    sf::Vector2i updated_mouse_position) {
    state.editor_state.selected_editor_square = updated_mouse_position;
}

void HouseSceneReducer::SetEntityTransform(sf::Vector2f new_transform) {
    state.entities[0].transform = new_transform;
}

void HouseSceneReducer::SetEntityVelocity(sf::Vector2f new_velocity) {
    state.entities[0].velocity = new_velocity;
}

void HouseSceneReducer::MousePressedAt() {
    state.editor_state.mouse_down = true;
}

void HouseSceneReducer::MouseReleased(sf::Vector2f release_mouse_position,
                                      int sprite_size) {
    if (state.editor_state.mouse_dragging) {
        auto delta = sf::Vector2f(
            (state.editor_state.mouse_down_at.x - release_mouse_position.x) *
                -1,
            (state.editor_state.mouse_down_at.y - release_mouse_position.y) *
                -1);

        state.editor_state.map_selection = sf::IntRect(
            round(state.editor_state.mouse_down_at.x / sprite_size),
            round(state.editor_state.mouse_down_at.y / sprite_size),
            round(delta.x / sprite_size), round(delta.y / sprite_size));
    }

    state.editor_state.mouse_down = false;
    state.editor_state.mouse_dragging = false;
}

void HouseSceneReducer::UpdateMousePosition(
    sf::Vector2f current_mouse_position) {
    if (state.editor_state.mouse_down) {
        auto delta =
            sf::Vector2f((state.editor_state.mouse_down_at.x -
                          state.editor_state.current_mouse_position.x) *
                             -1,
                         (state.editor_state.mouse_down_at.y -
                          state.editor_state.current_mouse_position.y) *
                             -1);

        if ((delta.x < 5 && delta.x > -5) || (delta.y < 5 && delta.y > -5)) {
            state.editor_state.mouse_dragging = false;
        } else {
            state.editor_state.mouse_dragging = true;
        }
    } else {
        state.editor_state.mouse_down_at = current_mouse_position;
    }

    state.editor_state.current_mouse_position = current_mouse_position;
}

void HouseSceneReducer::AddTool(Tool tool) {
    state.editor_state.tools.push_back(tool);
}

void HouseSceneReducer::SetPlayerState(EntityState new_player_state) {
    auto found_player = std::find_if(
        state.entities.begin(), state.entities.end(), [](const auto &entity) {
            return entity.type == EntityType::PlayerEntity;
        });

    if (found_player != state.entities.end()) {
        found_player->state = new_player_state;
    }
}

void HouseSceneReducer::SetPlayerDirection(sf::Vector2f new_direction) {
    auto found_player = std::find_if(
        state.entities.begin(), state.entities.end(), [](const auto &entity) {
            return entity.type == EntityType::PlayerEntity;
        });

    if (found_player != state.entities.end()) {
        if (new_direction.x != 0) {
            found_player->direction = new_direction;
        }
    }

    // First if the player has requested to loot something they are facing and close enough to
    auto angle = atan2f(new_direction.y, new_direction.x) * 180 / 3.1416;

    if (angle < 0) {
        angle += 360;
    }

    found_player->facing = angle;
}

void HouseSceneReducer::AddRoom(sf::IntRect new_room) {
    state.map.rooms.push_back(new_room);
}

void HouseSceneReducer::ClearEditorSelection() {
    state.editor_state.map_selection = sf::IntRect();
}

void HouseSceneReducer::InitEntityAIState(Entity& entity) {
    entity.ai.state = AIState::Patrolling;
}


void HouseSceneReducer::Attack(Entity& attacker, Entity& attackee) {
    attacker.ai.state = AIState::Attacking;

    // TODO 
    attacker.ai.target = std::weak_ptr<Entity>(std::make_shared<Entity>(attackee));
}

void HouseSceneReducer::SetMapBounds(sf::IntRect bounds) {
    state.map.bounds = bounds;
}

void HouseSceneReducer::MoveEntity(Entity& entity, sf::Vector2f transform) {
    entity.transform = transform;
}

void HouseSceneReducer::UpdateMap(MapState map) {
    // Update main struct
    // Copy entities from map to main
}
