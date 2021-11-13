#pragma once

#include <optional>

#include "AssetWatcher.h"
#include "HouseScene.h"
#include "ControllerScheme.h"
#include "Map.h"

class HouseSceneFactory {
    static std::shared_ptr<AssetWatcher> InitAssetWatcher();
    static AnimationMap InitAnimations(std::shared_ptr<AssetWatcher>);
    static std::vector<std::shared_ptr<TimedController>> InitControllers(
        std::shared_ptr<AssetWatcher>, 
        AnimationMap, 
        std::shared_ptr<ViewLayer>,
        std::shared_ptr<ViewLayer>
    );

    static std::shared_ptr<ControllerScheme> InitControllerScheme();

    static std::shared_ptr<ViewLayer> InitHouseMapViewLayer(
        std::shared_ptr<AssetWatcher>,
        AnimationMap, 
        sf::IntRect
    );

    static std::shared_ptr<ViewLayer> InitTilePaletteViewLayer();
    static std::shared_ptr<ViewLayer> InitToolbarViewLayer(std::shared_ptr<AssetWatcher>);

 public:
    static std::unique_ptr<HouseScene> Init(const int, const int, const std::optional<std::string>);
};

