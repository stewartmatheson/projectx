#include "HouseScene.h"
#include "Animation.h"
#include "Entity.h"
#include "EditorController.h"
#include "PlayerController.h"
#include "GridView.h"
#include "TileBackgroundView.h"
#include "TilePaletteView.h"
#include "EntityView.h"
#include "HouseSceneReducer.h"
#include "SelectedTileView.h"
#include "BoxSelectionView.h"

HouseScene::HouseScene(int window_width, int window_height, int offset, sf::IntRect map_bounds) :
offset(offset),
tile_map("./assets/house.png", 4, 16, 5, 7),
entity_map(4, 16),
player_sprite_sheet("./assets/NightThief.png", 4, 320, 1, 1),
house_map_view_layer(window_height, window_width),
tile_palette_view_layer(window_height, offset * 2 + tile_map.GetSpriteSize()),
reducer(state),
map(reducer) {
    Init(window_width, window_height);
    reducer.SetMapBounds(map_bounds);
}

HouseScene::HouseScene(int window_width, int window_height, int offset, std::string map_file_name) :
offset(offset),
tile_map("./assets/house.png", 4, 16, 5, 7),
entity_map(4, 16),
player_sprite_sheet("./assets/NightThief.png", 4, 320, 1, 1),
house_map_view_layer(window_height, window_width),
tile_palette_view_layer(window_height, offset * 2 + tile_map.GetSpriteSize()),
reducer(state),
map(reducer, map_file_name) {
    Init(window_width, window_height);
}

void HouseScene::Init(int window_width, int window_height) {
    player_animations = std::make_shared<std::unordered_map<EntityState, Animation>>();
    auto tile_sprites = tile_map.GetSprites();
    std::for_each(tile_sprites.begin(), tile_sprites.end(), [this](const auto &sprite){ 
        reducer.AddTilePaletteTile(TilePaletteTile{sprite, PaletteTile}, tile_map.GetSpriteSize());
    });

    auto entity_sprites = entity_map.GetSprites();
    reducer.AddTilePaletteTile(
        TilePaletteTile{entity_sprites[0], PaletteEntity, EntityType::GhostEntity},
        entity_map.GetSpriteSize()
    );

    reducer.AddTilePaletteTile(
        TilePaletteTile{entity_sprites[1], PaletteEntity, EntityType::DoorEntity}, 
        entity_map.GetSpriteSize()
    );

    auto left_toolbar_width = offset * 2 + tile_map.GetSpriteSize();
    auto total_height = (state.editor_state.tile_palette_tiles.size() * (tile_map.GetSpriteSize() + offset)) + offset;

    reducer.SetTilePaletteBounds(left_toolbar_width, window_height, total_height);
    state.editor_state.tile_palette_background = sf::RectangleShape(
        sf::Vector2f(left_toolbar_width, total_height)
    );
    state.editor_state.tile_palette_background.setFillColor(sf::Color(60,60,60, 255));

    state.editor_state.tile_palette_view = sf::View(sf::FloatRect(0, 0, left_toolbar_width, window_height));

    reducer.InitSelectionRectangle(tile_map.GetSpriteSize());

    std::vector<AnimationFrame> idle_frames;
    for (auto col = 0; col < 10; col++) {
        idle_frames.push_back(AnimationFrame{col, 0});
    }

    player_animations->insert(
        {EntityState::Idle, Animation(player_sprite_sheet, idle_frames, 32, 32, 8)}
    );

    std::vector<AnimationFrame> throw_frames;
    for (auto col = 0; col < 10; col++) {
        throw_frames.push_back(AnimationFrame{col, 1});
    }

    player_animations->insert(
        {EntityState::Throwing, Animation(player_sprite_sheet, throw_frames, 32, 32, 8) }
    );

    std::vector<AnimationFrame> walk_frames;
    for (auto col = 0; col < 10; col++) {
        walk_frames.push_back(AnimationFrame{col, 2});
    }

    player_animations->insert(
        {EntityState::Walking, Animation(player_sprite_sheet, walk_frames, 32, 32, 8) }
    );

    std::vector<AnimationFrame> attack_frames;
    for (auto col = 0; col < 10; col++) {
        attack_frames.push_back(AnimationFrame{col, 3});
    }

    player_animations->insert(
        {EntityState::Attacking, Animation(player_sprite_sheet, attack_frames, 32, 32, 8) }
    );

    std::vector<AnimationFrame> die_frames;
    for (auto col = 0; col < 10; col++) {
        die_frames.push_back(AnimationFrame{col, 4});
    }

    player_animations->insert(
        {EntityState::Dying, Animation(player_sprite_sheet, die_frames, 32, 32, 8) }
    );

    // Here now we know we have a valid state we execute an action to load the map. Note here that
    // if we ever intend to dispatch these actions more than once they should be added to a controller
    reducer.AddEntity(
        Entity(
            EntityType::PlayerEntity, 
            500.f, 
            .01f, 
            0, 
            0, 
            player_animations
        )
    );

    controllers.push_back(std::make_unique<EditorController>(
        entity_map.GetSpriteSize(),  
        tile_palette_view_layer.GetRenderTexture(),
        house_map_view_layer.GetRenderTexture(),
        map
    ));
 
    controllers.push_back(std::make_unique<PlayerController>());

    tile_palette_view_layer.AddView(
        std::make_unique<TilePaletteView>(
            tile_map, 
            entity_map, 
            window_height,
            left_toolbar_width
        )
    );

    house_map_view_layer.AddView(
        std::make_unique<SelectedTileView>(tile_map)
    );


    house_map_view_layer.AddView(
        std::make_unique<TileBackgroundView>(tile_map)
    );

    house_map_view_layer.AddView(
        std::make_unique<GridView>(tile_map.GetSpriteSize())
    );

    house_map_view_layer.AddView(
        std::make_unique<EntityView>(entity_map, player_animations)
    );

    house_map_view_layer.AddView(
        std::make_unique<BoxSelectionView>()
    );
}

void HouseScene::HandleInput(const EventWithMouse& event) {
    for(auto& controller : controllers)
        controller->HandleInput(event, reducer);
}

void HouseScene::Update() {
    for(auto& controller : controllers)
        controller->Update(reducer);

    for(auto& entity : state.entities)
        entity.Update();

    for(auto& player_animation : *player_animations)
        player_animation.second.Update();
}

void HouseScene::Draw(sf::RenderTarget& render_target) {
    house_map_view_layer.Draw(render_target, state.house_view, state);
    tile_palette_view_layer.Draw(render_target, state.editor_state.tile_palette_view, state);
}

