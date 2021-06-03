#include "HouseScene.h"
#include "Animation.h"
#include "Entity.h"
#include "EditorController.h"
#include "PlayerController.h"
#include "GridView.h"

HouseScene::HouseScene(int window_width, int window_height) :
tile_map("./assets/tilemap.png", 4, 16, 5, 7),
entity_map(4, 16),
player_sprite_sheet("./assets/NightThief.png", 4, 320, 1, 1),
player_animations(),
state() {

    std::vector<AnimationFrame> idle_frames;
    for (auto col = 0; col < 10; col++) {
        idle_frames.push_back(AnimationFrame{col, 0});
    }

    std::vector<AnimationFrame> throw_frames;
    for (auto col = 0; col < 10; col++) {
        throw_frames.push_back(AnimationFrame{col, 1});
    }

    std::vector<AnimationFrame> walk_frames;
    for (auto col = 0; col < 10; col++) {
        walk_frames.push_back(AnimationFrame{col, 2});
    }

    std::vector<AnimationFrame> attack_frames;
    for (auto col = 0; col < 10; col++) {
        attack_frames.push_back(AnimationFrame{col, 3});
    }

    std::vector<AnimationFrame> die_frames;
    for (auto col = 0; col < 10; col++) {
        die_frames.push_back(AnimationFrame{col, 4});
    }

    player_animations.insert(
        {EntityMode::Idle, Animation(player_sprite_sheet, idle_frames, 32, 32, 8)}
    );

    player_animations.insert(
        {EntityMode::Throwing, Animation(player_sprite_sheet, throw_frames, 32, 32, 8) }
    );

    player_animations.insert(
        {EntityMode::Walking, Animation(player_sprite_sheet, walk_frames, 32, 32, 8) }
    );

    player_animations.insert(
        {EntityMode::Attacking, Animation(player_sprite_sheet, attack_frames, 32, 32, 8) }
    );

    player_animations.insert(
        {EntityMode::Dying, Animation(player_sprite_sheet, die_frames, 32, 32, 8) }
    );


    // Here now we know we have a valid state we execute an action to load the map. Note here that
    // if we ever intend to dispatch these actions more than once they should be added to a controller
    reducer.LoadMap();
    reducer.AddPlayer();

    // This should be moved to the add player action
    state.entities.push_back({
        Entity<HouseSceneState>(EntityType::PlayerEntity, 500.f, .01f, player_animations)
    });

    scene_render_target.create(window_width, window_height);

    controllers.push_back(EditorController(
        entity_map.GetSpriteSize(),  
        tile_palette_render_texture,
        scene_render_target
    ));
    
    controllers.push_back(PlayerController());

    views.push_back(GridView(tile_map.GetSpriteSize()));
    views.push_back(TileBackgroundView());
    views.push_back(TilePaletteView());
    views.push_back(HouseSceneEntityView());
}

void HouseScene::HandleInput(EventWithMouse event) {
    std::for_each(
        controllers.begin(), 
        controllers.end(), 
        [&event, this](Controller<HouseSceneState>& controller){
            controller.HandleInput(event, state);
        }
    );
}

void HouseScene::Update() {
    std::for_each(controllers.begin(), controllers.end(), [this](Controller<HouseSceneState>& controller){
        controller.Update(state);
    });
    
    std::for_each(state.entities.begin(), state.entities.end(), [this](Entity<HouseSceneState>& entity){
        entity.Update(state);
    });
}

void HouseScene::Draw(sf::RenderTarget& render_target) {
    std::for_each(views.begin(), views.end(), [&render_target, this](View<HouseSceneState>& view){
        view.Draw(render_target, state);
    });
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
