
#include "HouseSceneState.h"
#include "View.h"

class SelectedTileView : public View<HouseSceneState> {
    const SpriteSheet &sprite_sheet;

  public:
    SelectedTileView(const SpriteSheet &);
    void Draw(sf::RenderTarget &, const HouseSceneState &) const;
};
