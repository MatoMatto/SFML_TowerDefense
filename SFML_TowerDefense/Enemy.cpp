#include "Enemy.h"
#include "pch.h"
#include "Game.h"

void Enemy::initBody() {
	
	this->body.setPosition(rand() % Global::window->getSize().x, rand() % Global::window->getSize().y);
	this->position = this->body.getPosition();
}

void Enemy::initText(){
	this->text.setFont(*this->font);
	this->text.setCharacterSize(10);
	this->text.setFillColor(sf::Color::White);
	this->text.setString("Hello");
}

void Enemy::initFont(sf::Font* font){
	this->font = font;
}

void Enemy::setPath(std::vector<Tile*>* path) {
	this->path = path;
}

void Enemy::initVars(){
	this->acceleration = float(rand() % 5 + 1) / 10;
	this->max_velocity = float(rand() % 15 + 15) / 2;
	this->radious = 10.f;
	this->currentTileIndex = 0;
}

Enemy::Enemy(sf::Font* font, Game* game, std::string type){
	this->game = game;
	this->setType(type);
	this->initVars();
	this->initBody();
	this->initFont(font);
	this->initText();
}


void Enemy::draw(sf::RenderTarget& target){
	target.draw(this->body);
	target.draw(this->text);
}

void Enemy::update(float FPS){
	this->move(FPS);
}

void Enemy::setTarget(sf::Vector2f target){
	this->target = target;
}

void Enemy::move(float FPS) {
	if (!this->currentTileIndex) {
		// Start one unit to the left of the first tile
		this->target = this->path->at(this->currentTileIndex++)->getPosition();
		this->target.x += Global::getUnit().x * .5f - Global::getUnit().x;
		this->target.y += Global::getUnit().y * .5f;
		this->position = target;
		this->body.setPosition(this->position);
		return;
	}
	if (this->currentTileIndex == this->path->size()) {
		this->target = this->path->at(this->currentTileIndex - 1)->getPosition();
		this->target.x += Global::getUnit().x * .5f + Global::getUnit().x;
		this->target.y += Global::getUnit().y * .5f;
	}
	sf::Vector2f direction = target - position;
	//std::cout << this->currentTileIndex << std::endl;
	// Calculate distance to target
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	// Normalize direction vector
	if (distance > 3.f) {
		direction /= distance;
	}
	else {
		if (this->reachedEnd()) {
			return;
		}

		// End one unit to the right of the last tile
		if (this->currentTileIndex == this->path->size() - 1) {
			this->target = this->path->at(this->currentTileIndex++)->getPosition();
			this->target.x += Global::getUnit().x * 1.5f;
			move(FPS);
			return;
		}

		this->target = this->path->at(this->currentTileIndex++)->getPosition();
		this->target.x += Global::getUnit().x * .5f;
		this->target.y += Global::getUnit().y * .5f;
		//std::cout << target.x << ", " << target.y << std::endl;
		move(FPS);
		return;
	}

	// Calculate movement vector
	sf::Vector2f movement = direction * (speed * 60 / FPS);
	//std::cout << position.x << " " << position.y << std::endl;
	// Update position
	position += movement;
	this->body.setPosition(position);
	this->text.setPosition(position);
	this->body.setRotation(atan2(movement.y, movement.x) * RAD_TO_DEG);
}

void Enemy::setType(std::string type) {
	this->type = type;
	std::fstream fs;
	fs.open("Resources/Enemies/" + type + ".txt");
	fs >> speed;
	fs >> health;
	fs.close();
	this->setTexture(this->game->getEnemyTextures()->at(type));
}

void Enemy::setTexture(sf::Texture& texture) {
	this->body.setTexture(texture);
	sf::Vector2f origin = { texture.getSize().x / 2.f, texture.getSize().y / 2.f };
	this->body.setOrigin(origin);
}

sf::Vector2f Enemy::getPosition() {
	return this->position;
}

bool Enemy::reachedEnd() {
	return this->currentTileIndex >= this->path->size();
}
