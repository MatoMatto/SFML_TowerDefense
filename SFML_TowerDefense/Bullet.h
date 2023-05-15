#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
class Game;
class Tower;

class Bullet {
	sf::Sprite sprite;
	Enemy* target;
	sf::Vector2f targetPos;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float speed, max_velocity;
	float acceleration;
	bool homing, valid;
	int damage;

	Game* game;
	Tower* owner;
public:
	void update();

	void setTarget(Enemy* enemy);
	Enemy* getTarget();

	void setStaticTarget(sf::Vector2f target);
	sf::Vector2f getStaticTarget();

	void moveToTarget();
	void setTexture(sf::Texture& texture);
	void drawTo(sf::RenderTarget& target);
	void rocketVelocity();
	void aimAtTarget();
	void checkEnemyCollision();
	void checkOutOfBounds();
	bool isValid();
	Bullet(Game* game, sf::Texture& texture, Tower* tower);

};

