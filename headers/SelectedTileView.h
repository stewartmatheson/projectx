
#include "HouseScene.h"

class SelectedTileView : public View<HouseSceneState> {
    int sprite_size;
public:
    SelectedTileView(int);
    void Draw(sf::RenderTarget&, const HouseSceneState&);
};
