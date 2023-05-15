#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include "Tile.h"
class Game;
class Enemy{
	sf::Vector2f velocity, position, target;
	float acceleration, max_velocity, radious;
	float speed;
	sf::Sprite body;
	sf::Text text;
	sf::Font* font;
	std::vector<Tile*>* path;
	int currentTileIndex;
	int health;
	Game* game;
	std::string type;

	void initBody();
	void initText();
	void initVars();
public:	
	Enemy(sf::Font* font, Game* game, std::string type);
	void initFont(sf::Font* font);
	void setPath(std::vector<Tile*>* path);
	void draw(sf::RenderTarget& target);
	void update(float FPS);
	void setTarget(sf::Vector2f target);
	void move(float FPS);
	void setType(std::string type);
	void setTexture(sf::Texture& texture);
	sf::Vector2f getPosition();

	bool reachedEnd();
};

