#include <fstream>
#include "Room.h"

Room* CreateRoom(int map_height, int map_width, int window_width, int window_height) {
    Room* room = (Room*)malloc(sizeof(*room));
    room->bounds = sf::IntRect(0, 0, map_width, map_height);
    room->tiles = new std::vector<Tile>();
    room->view = new sf::View(sf::FloatRect(0, 0, window_width, window_height));

    room->render_texture = new sf::RenderTexture();
    room->render_texture->create(window_width, window_height); 
    return room;
}

void DestructRoom(Room& room) {
    delete room.render_texture;
    delete room.view;
    delete room.tiles;
    free(&room);
}

void UpdateRoom(Room& room, const sf::Event& event, Editor& editor) {
    // Question : I'm dereferencing here but these functions accept pointers. Is this the right thing to do?
    EditorUpdateResult result = UpdateEditor(editor, event);
    
    if (result.type == EditorUpdateResult::Type::Save) {
        WriteRoomToFile(room, "./assets/maps/room.bin");
    } else if (result.type == EditorUpdateResult::Type::PlaceTile) {
        room.tiles->push_back(result.tile);
    } else if (result.type == EditorUpdateResult::Panning) {
        std::cout << result.mouse_delta.x << ", " << result.mouse_delta.y << std::endl;
        room.view->move(sf::Vector2f(result.mouse_delta.x * -1, result.mouse_delta.y * -1));
    }

} 

void DrawRoom(sf::RenderTarget& target, Room& room, TileMap& tile_map, Editor& editor) {
    room.render_texture->setView(*room.view);
    room.render_texture->clear();

    for(Tile tile : *room.tiles) {
        sf::Sprite sprite_to_draw((*tile_map.tiles)[tile.tile_map_index]);
        sprite_to_draw.setRotation(tile.rotation);
        int half_tile_size = tile_map.size * tile_map.scale / 2;
        sprite_to_draw.setPosition(
            (tile.x * tile_map.size * tile_map.scale) + half_tile_size,
            (tile.y * tile_map.size * tile_map.scale) + half_tile_size
        );
        sprite_to_draw.setOrigin(tile_map.size / 2, tile_map.size / 2);
        room.render_texture->draw(sprite_to_draw);
    }

    DrawEditor(*room.render_texture, editor, room.bounds.height, room.bounds.width);

    room.render_texture->display();
    sf::Sprite render_texture_sprite(room.render_texture->getTexture());
    target.draw(render_texture_sprite);
    DrawEditorTilePalette(target, editor);
}

void WriteRoomToFile(Room& room, std::string file_name) {
    std::ofstream wf(file_name, std::ios::out | std::ios::binary);

    if(!wf) {
        std::cout << "Can't open file!" << std::endl;
        exit(1);
    }

    wf.write(
        reinterpret_cast<const char *>(&room.bounds.left), 
        sizeof (room.bounds.left)
    );

    wf.write(
        reinterpret_cast<const char *>(&room.bounds.top), 
        sizeof (room.bounds.top)
    );

    wf.write(
        reinterpret_cast<const char *>(&room.bounds.width), 
        sizeof (room.bounds.width)
    );

    wf.write(
        reinterpret_cast<const char *>(&room.bounds.height), 
        sizeof (room.bounds.height)
    );

    int room_tile_count = room.tiles->size();
    wf.write(reinterpret_cast<const char *>(&room_tile_count), sizeof (room_tile_count));

    for(int i = 0; i < room_tile_count; i++) {
        wf.write(
            reinterpret_cast<const char *>(&(*room.tiles)[i].rotation), 
            sizeof ((*room.tiles)[i].rotation)
        );

        wf.write(
            reinterpret_cast<const char *>(&(*room.tiles)[i].tile_map_index), 
            sizeof ((*room.tiles)[i].tile_map_index)
        );

        wf.write(
            reinterpret_cast<const char *>(&(*room.tiles)[i].x), 
            sizeof ((*room.tiles)[i].x)
        );

        wf.write(
            reinterpret_cast<const char *>(&(*room.tiles)[i].y), 
            sizeof ((*room.tiles)[i].y)
        );
    }
}

Room* ReadRoomFromFile(std::string file_name) {
    std::ifstream rf(file_name, std::ios::in | std::ios::binary);

    if (!rf) {
        std::cout << "Can't read file!" << std::endl;
        exit(1);
    }
   

    int bounds_left, bounds_top, bounds_width, bounds_height;

    rf.read(
        reinterpret_cast<char *>(&bounds_left), 
        sizeof (bounds_left)
    );

    rf.read(
        reinterpret_cast<char *>(&bounds_top), 
        sizeof (bounds_top)
    );

    rf.read(
        reinterpret_cast<char *>(&bounds_width), 
        sizeof (bounds_width)
    );

    rf.read(
        reinterpret_cast<char *>(&bounds_height), 
        sizeof (bounds_height)
    );

    Room* room = (Room*)malloc(sizeof(*room));
    room->tiles = new std::vector<Tile>();
    room->bounds = sf::IntRect(bounds_left, bounds_top, bounds_width, bounds_height);


    int room_tile_count;
    rf.read(
        reinterpret_cast<char *>(&room_tile_count), 
        sizeof(room_tile_count)
    );


    for(int i = 0; i < room_tile_count; i++) {
        Tile tile;
        rf.read(
            reinterpret_cast<char *>(&tile.rotation), 
            sizeof (tile.rotation)
        );

        rf.read(
            reinterpret_cast<char *>(&tile.tile_map_index), 
            sizeof (tile.tile_map_index)
        );

        rf.read(
            reinterpret_cast<char *>(&tile.x), 
            sizeof (tile.x)
        );

        rf.read(
            reinterpret_cast<char *>(&tile.y), 
            sizeof (tile.y)
        );

        room->tiles->push_back(tile);
    }

    return room;
}
