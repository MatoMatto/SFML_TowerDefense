#include "Bullet.h"
#include "Game.h"
#include "Tower.h"
void Bullet::update() {
	if (this->target)targetPos = this->target->getPosition();
	this->moveToTarget();
	
}

void Bullet::setTarget(Enemy* enemy) {
	this->target = enemy;
}

Enemy* Bullet::getTarget() {
	return this->target;
}

void Bullet::setStaticTarget(sf::Vector2f target) {
	this->targetPos = target;
}

sf::Vector2f Bullet::getStaticTarget() {
	return this->targetPos;
}


void Bullet::moveToTarget() {
	if (!this->target) {
		if (velocity.x == 0 && velocity.y == 0) {
			sf::Vector2f dir = targetPos - position;
			float mag = std::sqrt(dir.x * dir.x + dir.y * dir.y);
			if (mag)dir /= mag;
			this->velocity = dir * (speed * 60/game->getFPS());
			this->aimAtTarget();
		}
		this->position += velocity;
		this->sprite.setPosition(this->position);
		return;
	}
	
	this->rocketVelocity();
}

void Bullet::setTexture(sf::Texture& texture) {
	this->sprite.setTexture(texture);
}
void Bullet::drawTo(sf::RenderTarget& target) {
	target.draw(sprite);
}
void Bullet::rocketVelocity() {
	sf::Vector2f diff = this->targetPos - this->position;

	// Calculate the angle to the target position
	float angle = atan2(diff.y, diff.x);

	// Calculate the new velocity based on the angle and acceleration
	sf::Vector2f new_velocity = this->velocity + acceleration * sf::Vector2f(cos(angle), sin(angle));

	// Cap the absolute value of the velocity at the maximum velocity
	float abs_vel = sqrt(new_velocity.x * new_velocity.x + new_velocity.y * new_velocity.y);
	if (abs_vel > max_velocity) {
		new_velocity *= max_velocity / abs_vel;
	}
	// Set the velocity
	this->velocity = new_velocity;
	sf::FloatRect bounds = this->sprite.getLocalBounds();
	if (this->position.x - bounds.width <= 0.f || this->position.x + bounds.width >= Global::window->getSize().x) {
		this->velocity.x *= -1.f;
		this->position.x = std::min(Global::window->getSize().x - (bounds.width + 1.f), std::max(this->position.x, 0.f + (bounds.width + 1.f)));
	}
	if (this->position.y - bounds.height <= 0.f || this->position.y + bounds.height >= Global::window->getSize().y) {
		this->velocity.y *= -1.f;
		this->position.y = std::min(Global::window->getSize().y - (bounds.height + 1.f), std::max(this->position.y, 0.f + (bounds.height + 1.f)));
	}
	this->sprite.setPosition(this->position);
	this->aimAtTarget();
}

void Bullet::aimAtTarget() {
	this->sprite.setRotation(atan2(velocity.x, velocity.x) * RAD_TO_DEG + 90);
}

Bullet::Bullet(Game* game, sf::Texture& texture, Tower* tower) {
	this->target = nullptr;
	this->owner = tower;
	this->position = tower->getPosition();
	this->max_velocity = 5;
	this->speed = 2;
	this->game = game;
	this->velocity = { 0,0 };
	this->acceleration = 2;
	this->sprite.setTexture(texture);
	this->sprite.setOrigin({ this->sprite.getLocalBounds().width / 2, this->sprite.getLocalBounds().height / 2 });
	this->sprite.setPosition(this->position);
	std::fstream fs;
	fs.open("Resources/Bullets/" + owner->getBulletType() + ".txt", std::ios::in);
	fs >> speed;
	max_velocity = speed;
	fs >> damage;
	fs >> homing;
	sf::Vector2f size;
	fs >> size.x >> size.y;
	this->sprite.setScale(size.x / this->sprite.getLocalBounds().width, size.y / this->sprite.getLocalBounds().height);
}
