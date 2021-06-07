#include "HouseScene.h"
#include "Animation.h"
#include "Entity.h"
#include "EditorController.h"
#include "PlayerController.h"
#include "GridView.h"
#include "TileBackgroundView.h"
#include "TilePaletteView.h"
#include "HouseSceneEntityView.h"
#include "EntityView.h"
#include "HouseSceneReducer.h"

HouseScene::HouseScene(int window_width, int window_height, sf::IntRect map_bounds) :
tile_map("./assets/tilemap.png", 4, 16, 5, 7),
entity_map(4, 16),
player_sprite_sheet("./assets/NightThief.png", 4, 320, 1, 1),
state(),
reducer(state),
map(reducer) {
    Init(window_width, window_height);
}

HouseScene::HouseScene(int window_width, int window_height, std::string map_file_name) :
tile_map("./assets/tilemap.png", 4, 16, 5, 7),
entity_map(4, 16),
player_sprite_sheet("./assets/NightThief.png", 4, 320, 1, 1),
state(),
controllers(),
views(),
player_animations(),
reducer(state),
map(reducer, map_file_name) {
    Init(window_width, window_height);
}

void HouseScene::Init(int window_width, int window_height) {

    std::vector<AnimationFrame> idle_frames;
    for (auto col = 0; col < 10; col++) {
        idle_frames.push_back(AnimationFrame{col, 0});
    }

    player_animations.insert(
        {EntityState::Idle, Animation(player_sprite_sheet, idle_frames, 32, 32, 8)}
    );

    std::vector<AnimationFrame> throw_frames;
    for (auto col = 0; col < 10; col++) {
        throw_frames.push_back(AnimationFrame{col, 1});
    }

    player_animations.insert(
        {EntityState::Throwing, Animation(player_sprite_sheet, throw_frames, 32, 32, 8) }
    );

    std::vector<AnimationFrame> walk_frames;
    for (auto col = 0; col < 10; col++) {
        walk_frames.push_back(AnimationFrame{col, 2});
    }

    player_animations.insert(
        {EntityState::Walking, Animation(player_sprite_sheet, walk_frames, 32, 32, 8) }
    );

    std::vector<AnimationFrame> attack_frames;
    for (auto col = 0; col < 10; col++) {
        attack_frames.push_back(AnimationFrame{col, 3});
    }

    player_animations.insert(
        {EntityState::Attacking, Animation(player_sprite_sheet, attack_frames, 32, 32, 8) }
    );

    std::vector<AnimationFrame> die_frames;
    for (auto col = 0; col < 10; col++) {
        die_frames.push_back(AnimationFrame{col, 4});
    }

    player_animations.insert(
        {EntityState::Dying, Animation(player_sprite_sheet, die_frames, 32, 32, 8) }
    );

    // Here now we know we have a valid state we execute an action to load the map. Note here that
    // if we ever intend to dispatch these actions more than once they should be added to a controller
    auto player_entity = Entity(EntityType::PlayerEntity, 500.f, .01f, 0, 0, player_animations);
    reducer.AddEntity(player_entity);

    scene_render_target.create(window_width, window_height);

    controllers.push_back(std::make_unique<EditorController>(
        entity_map.GetSpriteSize(),  
        tile_palette_render_texture,
        scene_render_target,
        map
    ));
    
    controllers.push_back(std::make_unique<PlayerController>(player_entity));
    
    views.push_back(std::make_unique<GridView>(tile_map.GetSpriteSize()));
    views.push_back(std::make_unique<TileBackgroundView>(tile_map));
    views.push_back(std::make_unique<HouseSceneEntityView>(entity_map));
    views.push_back(std::make_unique<EntityView>(
        player_entity, 
        player_sprite_sheet,
        player_animations
    ));
    
    views.push_back(std::make_unique<TilePaletteView>(
        tile_map, 
        entity_map, 
        tile_palette_render_texture,
        window_height
    ));
}

void HouseScene::HandleInput(EventWithMouse event) {
    for(auto& controller : controllers)
        controller->HandleInput(event, reducer);
}

void HouseScene::Update() {
    for(auto& controller : controllers)
        controller->Update(reducer);

    for(auto& entity : state.entities)
        entity.Update();

    for(auto& player_animation : player_animations)
        player_animation.second.Update();
}

void HouseScene::Draw(sf::RenderTarget& render_target) {
    for(auto& view : views)
        view->Draw(render_target, state);
}

/*
void HouseScene::Draw(sf::RenderTarget& target) {
    if (!editor_enabled) {
        house_view.setCenter(player.GetTransform());
    }

    // Draw Room and Grid
    house_render_texture.setView(house_view);
    house_render_texture.clear();


    player.Draw(house_render_texture);


    house_render_texture.display();

    sf::Sprite house_render_sprite(house_render_texture.getTexture());
    target.draw(house_render_sprite);

    if (editor_enabled) {
        //Draw Tile Palette
        tile_palette_view.Draw(target);
    }

}
*/
