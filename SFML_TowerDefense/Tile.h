#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
class Tile{
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Vector2i index;
	int tileType;
public:
	Tile(sf::Texture& texture, sf::Vector2f position, int tileType);
	void setTexture(sf::Texture& texture);
	void drawTo(sf::RenderTarget& target);
	short getType();
	sf::Vector2i getIndex();
	sf::Vector2f getPosition();
};

