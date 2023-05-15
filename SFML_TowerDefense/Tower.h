#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "Enemy.h"
#include "Bullet.h"
class Game;
class Tower{
	int price, damageDelt;
	float radious, shootDelay;
	bool isSelected;
	std::string name;
	sf::Vector2f size, position;
	sf::Sprite sprite, base;
	sf::Texture tt, bt;
	sf::CircleShape range;
	sf::Clock shootTimer;
	std::string bulletName;
	sf::Vector2f enemyPos;
	Enemy* target;
	Game* game;
	std::vector<Bullet*> bullets;
public:
	Tower(std::string name, sf::Vector2f position, Game* game, sf::Texture& texture);
	~Tower();
	void setSelected(bool sel);
	void draw(sf::RenderTarget& target);
	void update();
	void setTarget(Enemy* target);
	void updateTarget();
	void aimAtTarget();
	void aimAtMouse();
	void shoot();
	std::string getBulletType();
	sf::Vector2f getPosition();
};

