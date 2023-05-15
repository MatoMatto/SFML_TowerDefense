#pragma once
#include <SFML/Graphics.hpp>
#include "Tower.h"

class Game;

class TowerPlace {
	std::string name;
	sf::Sprite sprite;
	float radius, shootDelay;
	int price;
	sf::CircleShape range;
	std::vector<Tower*>* gameTowers;
	Game* game;
	sf::Texture* texture;
	sf::Vector2f position;
	bool placing;
public:
	TowerPlace(Game* game);
	void click();
	bool canPlace();
	void update();
	void drawTo(sf::RenderTarget& target);
	void setTexture(sf::Texture& texture);
	void setTower(std::string tower, sf::Texture& texture);
	void reset();
};