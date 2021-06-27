#include "HouseScene.h"
#include "Animation.h"
#include "BoxSelectionView.h"
#include "EditorController.h"
#include "Entity.h"
#include "EntityView.h"
#include "GridSelectionView.h"
#include "GridView.h"
#include "HouseSceneReducer.h"
#include "PlayerController.h"
#include "SelectedTileView.h"
#include "TileBackgroundView.h"
#include "TilePaletteView.h"
#include "ToolbarController.h"
#include "ToolbarToolsView.h"

HouseScene::HouseScene(int window_width, int window_height,
                       int tile_palette_offset, int toolbar_offset,
                       sf::IntRect map_bounds)
    : tile_map("./assets/house.png", state.scale, 16, 5, 7),
      entity_map(state.scale, 16),
      player_sprite_sheet("./assets/NightThief.png", state.scale, 320, 1, 1),
      toolbar_sprite_sheet(state.scale, 8),
      tile_palette_offset(tile_palette_offset), toolbar_offset(toolbar_offset),
      house_map_view_layer(sf::IntRect(0, 0, window_width, window_height)),
      tile_palette_view_layer(
          sf::IntRect(0, 0, tile_palette_offset * 2 + tile_map.GetSpriteSize(),
                      window_height)),
      toolbar_view_layer(
          sf::IntRect(tile_palette_offset * 2 + tile_map.GetSpriteSize(), 0,
                      window_width, 60)),
      reducer(state), map(reducer) {
    Init(window_width, window_height);
    reducer.SetMapBounds(map_bounds);
}

HouseScene::HouseScene(int window_width, int window_height,
                       int tile_palette_offset, int toolbar_offset,
                       std::string map_file_name)
    : tile_map("./assets/house.png", state.scale, 16, 5, 7),
      entity_map(state.scale, 16),
      player_sprite_sheet("./assets/NightThief.png", state.scale, 320, 1, 1),
      toolbar_sprite_sheet(state.scale, state.editor_state.toolbar_icon_size),
      tile_palette_offset(tile_palette_offset), toolbar_offset(toolbar_offset),
      house_map_view_layer(sf::IntRect(0, 0, window_width, window_height)),
      tile_palette_view_layer(
          sf::IntRect(0, 0, tile_palette_offset * 2 + tile_map.GetSpriteSize(),
                      window_height)),
      toolbar_view_layer(
          sf::IntRect(tile_palette_offset * 2 + tile_map.GetSpriteSize(), 0,
                      window_width, 60)),
      reducer(state), map(reducer, map_file_name) {
    Init(window_width, window_height);
}

void HouseScene::Init(int window_width, int window_height) {
    // TODO : When we have to build a graphics settings page we will need to
    // move this.
    reducer.SetWindowSize(window_width, window_height);

    // TODO : Not sure we even want this here. We really need to rethink where
    // all this init code will live
    reducer.SetLeftToolbarWidth(tile_palette_offset * 2 +
                                tile_map.GetSpriteSize());

    player_animations =
        std::make_shared<std::unordered_map<EntityState, Animation>>();
    auto tile_sprites = tile_map.GetSprites();
    std::for_each(
        tile_sprites.begin(), tile_sprites.end(), [this](const auto &sprite) {
            reducer.AddTilePaletteTile(TilePaletteTile{sprite, PaletteTile},
                                       tile_map.GetSpriteSize());
        });

    InitEntityMap();
    InitToolbarMap();
    InitTools();

    auto entity_sprites = entity_map.GetSprites();
    reducer.AddTilePaletteTile(TilePaletteTile{entity_sprites[0], PaletteEntity,
                                               EntityType::GhostEntity},
                               entity_map.GetSpriteSize());

    reducer.AddTilePaletteTile(TilePaletteTile{entity_sprites[1], PaletteEntity,
                                               EntityType::DoorEntity},
                               entity_map.GetSpriteSize());

    auto total_height = (state.editor_state.tile_palette_tiles.size() *
                         (tile_map.GetSpriteSize() + tile_palette_offset)) +
                        tile_palette_offset;

    reducer.SetTilePaletteBounds(state.editor_state.left_toolbar_width,
                                 window_height, total_height);
    state.editor_state.tile_palette_background = sf::RectangleShape(
        sf::Vector2f(state.editor_state.left_toolbar_width, total_height));

    state.editor_state.tile_palette_background.setFillColor(
        sf::Color(60, 60, 60, 255));
    state.editor_state.tile_palette_view = sf::View(sf::FloatRect(
        0, 0, state.editor_state.left_toolbar_width, window_height));
    state.editor_state.toolbar_view =
        sf::View(sf::FloatRect(0, 0, window_width, toolbar_offset));
    state.house_view =
        sf::View(sf::FloatRect(0, 0, window_width, window_height));

    reducer.InitSelectionRectangle(tile_map.GetSpriteSize());

    InitAnimations();

    // Here now we know we have a valid state we execute an action to load the
    // map. Note here that if we ever intend to dispatch these actions more than
    // once they should be added to a controller
    reducer.AddEntity(
        Entity(EntityType::PlayerEntity, 500.f, .01f, 0, 0, player_animations));

    controllers.push_back(std::make_unique<EditorController>(
        entity_map.GetSpriteSize(), tile_palette_view_layer.GetRenderTexture(),
        house_map_view_layer.GetRenderTexture(), map));

    controllers.push_back(std::make_unique<ToolbarController>());
    controllers.push_back(std::make_unique<PlayerController>());

    tile_palette_view_layer.AddView(std::make_unique<TilePaletteView>(
        tile_map, entity_map, window_height,
        state.editor_state.left_toolbar_width));

    toolbar_view_layer.AddView(
        std::make_unique<ToolbarToolsView>(toolbar_sprite_sheet));

    InitHouseMapView();
}

void HouseScene::InitTools() { reducer.AddTool(Tool{ToolType::Room, 0}); }

void HouseScene::InitEntityMap() {
    entity_map.CreateIconSprite(sf::Color::Red, 0);
    entity_map.CreateIconSprite(sf::Color::Green, 1);
}

void HouseScene::InitToolbarMap() {
    toolbar_sprite_sheet.CreateIconSprite(sf::Color::Blue, 0);
}

void HouseScene::InitAnimations() {
    std::vector<AnimationFrame> idle_frames;
    for (auto col = 0; col < 10; col++) {
        idle_frames.push_back(AnimationFrame{col, 0});
    }

    player_animations->insert(
        {EntityState::Idle,
         Animation(player_sprite_sheet, idle_frames, 32, 32, 8)});

    std::vector<AnimationFrame> throw_frames;
    for (auto col = 0; col < 10; col++) {
        throw_frames.push_back(AnimationFrame{col, 1});
    }

    player_animations->insert(
        {EntityState::Throwing,
         Animation(player_sprite_sheet, throw_frames, 32, 32, 8)});

    std::vector<AnimationFrame> walk_frames;
    for (auto col = 0; col < 10; col++) {
        walk_frames.push_back(AnimationFrame{col, 2});
    }

    player_animations->insert(
        {EntityState::Walking,
         Animation(player_sprite_sheet, walk_frames, 32, 32, 8)});

    std::vector<AnimationFrame> attack_frames;
    for (auto col = 0; col < 10; col++) {
        attack_frames.push_back(AnimationFrame{col, 3});
    }

    player_animations->insert(
        {EntityState::Attacking,
         Animation(player_sprite_sheet, attack_frames, 32, 32, 8)});

    std::vector<AnimationFrame> die_frames;
    for (auto col = 0; col < 10; col++) {
        die_frames.push_back(AnimationFrame{col, 4});
    }

    player_animations->insert(
        {EntityState::Dying,
         Animation(player_sprite_sheet, die_frames, 32, 32, 8)});
}

void HouseScene::InitHouseMapView() {
    house_map_view_layer.AddView(std::make_unique<SelectedTileView>(tile_map));

    house_map_view_layer.AddView(
        std::make_unique<TileBackgroundView>(tile_map));

    house_map_view_layer.AddView(
        std::make_unique<GridView>(tile_map.GetSpriteSize()));

    house_map_view_layer.AddView(
        std::make_unique<EntityView>(entity_map, player_animations));

    house_map_view_layer.AddView(std::make_unique<BoxSelectionView>());

    house_map_view_layer.AddView(
        std::make_unique<GridSelectionView>(tile_map.GetSpriteSize()));
}

void HouseScene::HandleInput(const EventWithMouse &event) {
    for (auto &controller : controllers)
        controller->HandleInput(event, reducer);
}

void HouseScene::Update() {
    for (auto &controller : controllers)
        controller->Update(reducer);

    for (auto &entity : state.entities)
        entity.Update();

    for (auto &player_animation : *player_animations)
        player_animation.second.Update();
}

void HouseScene::Draw(sf::RenderTarget &render_target) {
    house_map_view_layer.Draw(render_target, state.house_view, state);
    toolbar_view_layer.Draw(render_target, state.editor_state.toolbar_view,
                            state);
    tile_palette_view_layer.Draw(render_target,
                                 state.editor_state.tile_palette_view, state);
}
