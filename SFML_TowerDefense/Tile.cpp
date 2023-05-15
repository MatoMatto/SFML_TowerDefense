#include "Tile.h"

Tile::Tile(sf::Texture& texture, sf::Vector2f position, int tileType){
	this->sprite.setTexture(texture);
	this->sprite.setScale(
		Global::getUnit().x / this->sprite.getLocalBounds().width,
		Global::getUnit().y / this->sprite.getLocalBounds().height
	);
	this->index = (sf::Vector2i)position;
	this->position = { position.x * Global::getUnit().x, position.y * Global::getUnit().y};
	this->sprite.setPosition(this->position);
	this->tileType = tileType;
}

void Tile::setTexture(sf::Texture& texture){
	this->sprite.setTexture(texture);
}

void Tile::drawTo(sf::RenderTarget& target){
	target.draw(this->sprite);
}

short Tile::getType() {
	return this->tileType;
}

sf::Vector2i Tile::getIndex() {
	return this->index;
}

sf::Vector2f Tile::getPosition(){
	return this->position;
}
