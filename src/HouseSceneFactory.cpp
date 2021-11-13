#include "HouseSceneFactory.h"
#include "AssetWatcher.h"
#include "BoxSelectionView.h"
#include "ControllerScheme.h"
#include "CreatedRoomSelectionView.h"
#include "EditorController.h"
#include "EntityFactory.h"
#include "EntityView.h"
#include "GamepadControllerScheme.h"
#include "GridSelectionView.h"
#include "GridView.h"
#include "KeyboardControllerScheme.h"
#include "PlayerController.h"
#include "SelectedTileView.h"
#include "ShadowView.h"
#include "SpriteSheet.h"
#include "TileBackgroundView.h"
#include "TilePaletteView.h"
#include "ToolbarController.h"
#include "ToolbarToolsView.h"
#include "AIController.h"
#include <vector>
#include <optional>

std::unique_ptr<HouseScene>
HouseSceneFactory::Init(const int screen_height, const int screen_width,
                        const std::optional<std::string> map_path_optional) {
    auto asset_watcher = InitAssetWatcher();
    auto reducer = std::make_shared<HouseSceneReducer>();

    // Create Tile Sprites
    auto tile_sprites = asset_watcher->GetSpriteSheet("tile_map")->GetSprites();

    std::for_each(
        tile_sprites.begin(), tile_sprites.end(),
        [&asset_watcher, &reducer](const auto &sprite) {
            reducer->AddTilePaletteTile(
                TilePaletteTile{sprite, TilePaletteType::PaletteTile},
                asset_watcher->GetSpriteSheet("tile_map")->GetSpriteSize());
        });

    // TODO : This method might need to move out of here at some point
    asset_watcher->GetSpriteSheet("entity_map")
        ->CreateIconSprite(sf::Color::Red, 0);
    asset_watcher->GetSpriteSheet("entity_map")
        ->CreateIconSprite(sf::Color::Green, 1);
    asset_watcher->GetSpriteSheet("toolbar_sprite_sheet")
        ->CreateIconSprite(sf::Color::Yellow, 0);

    auto entity_sprites =
        asset_watcher->GetSpriteSheet("entity_map")->GetSprites();
    reducer->AddTilePaletteTile(
        TilePaletteTile{entity_sprites[0], TilePaletteType::PaletteEntity,
                        EntityType::GhostEntity},
        asset_watcher->GetSpriteSheet("entity_map")->GetSpriteSize());

    reducer->AddTilePaletteTile(
        TilePaletteTile{entity_sprites[1], TilePaletteType::PaletteEntity,
                        EntityType::DoorEntity},
        asset_watcher->GetSpriteSheet("entity_map")->GetSpriteSize());

    if (map_path_optional.has_value()) {
        reducer->UpdateMap(Map::ReadFromFile(map_path_optional.value()));
    } else {
        reducer->UpdateMap(Map::New());
    }

    auto animations = InitAnimations(asset_watcher);
    auto tile_pallette_view_layer = InitTilePaletteViewLayer();
    auto house_map_view_layer = InitHouseMapViewLayer(
        asset_watcher, 
        animations, 
        reducer->GetState().map.bounds
    );
    auto view_layers = std::list<std::shared_ptr<ViewLayer>>();

    view_layers.push_back(house_map_view_layer);
    view_layers.push_back(InitToolbarViewLayer(asset_watcher));
    view_layers.push_back(tile_pallette_view_layer);

    auto controller_list =
        InitControllers(
                asset_watcher, 
                animations, 
                tile_pallette_view_layer,
                house_map_view_layer
                );

    reducer->InitSelectionRectangle(
        asset_watcher->GetSpriteSheet("tile_map")->GetSpriteSize());
    reducer->AddEntity(EntityFactory::Player(sf::Vector2f(0, 0)));

    reducer->AddTool(Tool{ToolType::Room, 0});

    return std::make_unique<HouseScene>(asset_watcher, controller_list,
                                        view_layers, animations, reducer);
}

std::shared_ptr<ControllerScheme> HouseSceneFactory::InitControllerScheme() {
    if (sf::Joystick::isConnected(0)) {
        return std::make_shared<GamepadControllerScheme>();
    } else {
        return std::make_shared<KeyboardControllerScheme>();
    }
}

std::vector<std::shared_ptr<TimedController>> HouseSceneFactory::InitControllers(
    std::shared_ptr<AssetWatcher> asset_watcher,
    AnimationMap animations,
    std::shared_ptr<ViewLayer> tile_pallette_view_layer,
    std::shared_ptr<ViewLayer> house_map_view_layer
) {
    auto controller_list = std::vector<std::shared_ptr<TimedController>>();
    auto controller_scheme = InitControllerScheme();

    controller_list.push_back(std::make_shared<TimedController>(
        std::make_unique<EditorController>(
            asset_watcher->GetSpriteSheet("entity_map")->GetSpriteSize(),
            tile_pallette_view_layer->GetRenderTexture(),
            house_map_view_layer->GetRenderTexture(), 
            *house_map_view_layer, *tile_pallette_view_layer)));

    controller_list.push_back(std::make_shared<TimedController>(
       std::make_unique<ToolbarController>()));

    controller_list.push_back(std::make_shared<TimedController>(
        std::make_unique<PlayerController>(animations, controller_scheme, 
                                           *house_map_view_layer)));


    controller_list.push_back(std::make_unique<TimedController>(
                std::make_unique<AIController>())
            );
    return controller_list;
}

std::shared_ptr<AssetWatcher>
HouseSceneFactory::InitAssetWatcher() {
    auto asset_watcher = std::make_shared<AssetWatcher>(Screen::GetScale());

    asset_watcher->RegisterSpriteSheet(
        "tile_map",
        std::make_shared<SpriteSheet>("./assets/house.png", Map::GetSpriteSize(), 20, 20)
    );

    asset_watcher->RegisterSpriteSheet(
        "entity_map", std::make_shared<SpriteSheet>(16));

    asset_watcher->RegisterSpriteSheet(
        "player_sprite_sheet",
        std::make_shared<SpriteSheet>("./assets/NightThief.png", 320, 1, 1));

    asset_watcher->RegisterSpriteSheet(
        "toolbar_sprite_sheet", std::make_shared<SpriteSheet>(8));

    return asset_watcher;
}

std::shared_ptr<std::unordered_map<EntityState, Animation>>
HouseSceneFactory::InitAnimations(
    std::shared_ptr<AssetWatcher> asset_watcher) {
    std::shared_ptr<std::unordered_map<EntityState, Animation>>
        player_animations =
            std::make_shared<std::unordered_map<EntityState, Animation>>();

    std::vector<AnimationFrame> idle_frames;
    for (auto col = 0; col < 10; col++) {
        idle_frames.push_back(AnimationFrame{col, 0});
    }

    player_animations->insert(
        {EntityState::Idle,
         Animation(asset_watcher->GetSpriteSheet("player_sprite_sheet"),
                   idle_frames, 32, 32, 8)});

    std::vector<AnimationFrame> throw_frames;
    for (auto col = 0; col < 10; col++) {
        throw_frames.push_back(AnimationFrame{col, 1});
    }

    player_animations->insert(
        {EntityState::Throwing,
         Animation(asset_watcher->GetSpriteSheet("player_sprite_sheet"),
                   throw_frames, 32, 32, 8)});

    std::vector<AnimationFrame> walk_frames;
    for (auto col = 0; col < 10; col++) {
        walk_frames.push_back(AnimationFrame{col, 2});
    }

    player_animations->insert(
        {EntityState::Walking,
         Animation(asset_watcher->GetSpriteSheet("player_sprite_sheet"),
                   walk_frames, 32, 32, 8)});

    std::vector<AnimationFrame> attack_frames;
    for (auto col = 0; col < 10; col++) {
        attack_frames.push_back(AnimationFrame{col, 3});
    }

    player_animations->insert(
        {EntityState::Attacking,
         Animation(asset_watcher->GetSpriteSheet("player_sprite_sheet"),
                   attack_frames, 32, 32, 8)});

    std::vector<AnimationFrame> die_frames;
    for (auto col = 0; col < 10; col++) {
        die_frames.push_back(AnimationFrame{col, 4});
    }

    player_animations->insert(
        {EntityState::Dying,
         Animation(asset_watcher->GetSpriteSheet("player_sprite_sheet"),
                   die_frames, 32, 32, 8)});

    return player_animations;
}

std::shared_ptr<ViewLayer> HouseSceneFactory::InitHouseMapViewLayer(
    std::shared_ptr<AssetWatcher> asset_watcher,
    AnimationMap player_animations,
    sf::IntRect map_bounds
) {
    sf::View house_map_view = sf::View(sf::FloatRect(
        0, 0, Screen::GetWindowSize().width, Screen::GetWindowSize().height));

    auto house_map_view_layer = std::make_shared<ViewLayer>(Screen::GetWindowSize(), house_map_view);

    house_map_view_layer->AddView(std::make_unique<SelectedTileView>(
        asset_watcher->GetSpriteSheet("tile_map")));

    house_map_view_layer->AddView(std::make_unique<TileBackgroundView>(
        asset_watcher->GetSpriteSheet("tile_map")));

    house_map_view_layer->AddView(std::make_unique<GridView>(
        asset_watcher->GetSpriteSheet("tile_map")->GetSpriteSize()));

    house_map_view_layer->AddView(std::make_unique<EntityView>(
        asset_watcher->GetSpriteSheet("entity_map"), player_animations));

    house_map_view_layer->AddView(std::make_unique<BoxSelectionView>());
    house_map_view_layer->AddView(
        std::make_unique<CreatedRoomSelectionView>());

    house_map_view_layer->AddView(std::make_unique<GridSelectionView>(
        asset_watcher->GetSpriteSheet("tile_map")->GetSpriteSize()));

    house_map_view_layer->AddView(std::make_unique<ShadowView>(
        sf::IntRect(0, 0,
                    asset_watcher->GetSpriteSheet("tile_map")->GetSpriteSize() *
                        map_bounds.width,
                    asset_watcher->GetSpriteSheet("tile_map")->GetSpriteSize() *
                        map_bounds.height)));

    return house_map_view_layer;
}

std::shared_ptr<ViewLayer> HouseSceneFactory::InitTilePaletteViewLayer() {
    
    auto tile_palette_texture_size = Screen::GetTilePaletteArea();
    sf::View tile_palette_view = sf::View(sf::FloatRect(
        0, 0, Screen::GetTilePaletteArea().width, Screen::GetWindowSize().height));
    auto tile_pallette_view_layer = std::make_shared<ViewLayer>(tile_palette_texture_size, tile_palette_view);
    tile_pallette_view_layer->AddView(std::make_unique<TilePaletteView>(
        Screen::GetWindowSize().height, Screen::GetTilePaletteArea().width));

    return tile_pallette_view_layer;
}

std::shared_ptr<ViewLayer> HouseSceneFactory::InitToolbarViewLayer(
    std::shared_ptr<AssetWatcher> asset_watcher
) {
    //auto toolbar_texture_size = Sceen::GetToolbarArea();
    sf::View toolbar_view = sf::View(sf::FloatRect(0, 0, Screen::GetWindowSize().width, Screen::GetToolbarOffset()));
    auto toolbar_view_layer = std::make_shared<ViewLayer>(Screen::GetToolbarArea(), toolbar_view);
    toolbar_view_layer->AddView(std::make_unique<ToolbarToolsView>(
        asset_watcher->GetSpriteSheet("toolbar_sprite_sheet")));

    return toolbar_view_layer;
}

