#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Editor.h"

// A map holds all data for a given tile layout within the game.
struct Room {
    sf::IntRect bounds;
	// std::vector<sf::Sprite>* tiles;
	std::vector<Tile>* tiles;

    sf::RenderTexture* render_texture;

    sf::View* view;

};

/**
 * @brief 
 *
 * @param int window_height
 * @param int window_width
 * @param int map_height
 * @param int map_width
 *
 * @return The created room
 */
Room *CreateRoom(int, int, int, int);

void DestructRoom(Room &);

void UpdateRoom(Room &, const sf::Event &, Editor &);

void DrawRoom(sf::RenderTarget &, Room &, TileMap &, Editor &);

void WriteRoomToFile(Room &, std::string);

Room *ReadRoomFromFile(std::string);

