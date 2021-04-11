#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Editor.h"

// A map holds all data for a given tile layout within the game.
typedef struct {
    sf::IntRect bounds;
	// std::vector<sf::Sprite>* tiles;
	std::vector<Tile>* tiles;
} Room;

Room *CreateRoom(int, int, int);

void DestructRoom(Room &);

void UpdateRoom(Room &, const sf::Event &, Editor &);

void DrawRoom(sf::RenderTarget &, Room &, TileMap &);

void DrawRoom(sf::RenderTarget &, Room &, TileMap &, Editor &);

void WriteRoomToFile(Room &, std::string);

Room *ReadRoomFromFile(std::string);

