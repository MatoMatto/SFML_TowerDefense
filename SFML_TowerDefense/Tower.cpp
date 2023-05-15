#include "Tower.h"
#include "pch.h"
#include "Game.h"
Tower::Tower(std::string name, sf::Vector2f position, Game* game, sf::Texture& texture) {
	this->name = name;
	std::fstream fs;
	fs.open("Resources/Towers/" + name + ".txt", std::ios::in);
	fs >> this->price;
	fs >> this->shootDelay;
	fs >> radious;
	fs >> bulletName;
	fs.close();
	this->size = { TOWER_SIZE, TOWER_SIZE };
	this->isSelected = true;
	this->damageDelt = 0;
	this->target = nullptr;

	this->position = position;
	this->game = game;

	this->range.setRadius(radious);
	this->range.setOrigin(radious, radious);
	this->range.setPosition(position);


	sprite.setTexture(texture);
	base.setTexture(this->game->getBaseTexture());

	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);

	float scale = TOWER_SIZE / sprite.getLocalBounds().width;
	sprite.setScale(scale, scale);


	this->base.setOrigin(this->game->getBaseTexture().getSize().x / 2.f, this->game->getBaseTexture().getSize().y / 2.f);
	this->base.setScale({ TOWER_SIZE / this->base.getLocalBounds().width,TOWER_SIZE / this->base.getLocalBounds().height });

	sprite.setPosition(position);
	base.setPosition(position);
}

Tower::~Tower() {
	for (auto& e : this->bullets)delete e;
}

void Tower::setSelected(bool sel) {
	this->isSelected = sel;
}

void Tower::draw(sf::RenderTarget& target) {
	if (this->isSelected)target.draw(range);
	target.draw(base);
	for (auto& e : this->bullets) {
		e->drawTo(target);
	}
	target.draw(sprite);

}


void Tower::update() {
	updateTarget();

	if (target) {
		aimAtTarget();

		if (shootDelay <= shootTimer.getElapsedTime().asSeconds()) {
			shoot();
			shootTimer.restart();
		}
	}

	for (auto& e : this->bullets) {
		e->update();
		if (!e->isValid()) {
			this->bullets.erase(std::remove_if(this->bullets.begin(), this->bullets.end(), [](Bullet* bullet) {
				bool isValid = bullet->isValid();
				if (!isValid) {
					delete bullet;
				}
				return !isValid;
			}), this->bullets.end());
		}
	}
}

void Tower::shoot() {
	Bullet* bullet = new Bullet(this->game, this->game->getBulletTextures()->at(bulletName), this);
	bullet->setStaticTarget(enemyPos);
	bullet->setTarget(target);
	this->bullets.push_back(bullet);
}
std::vector<Bullet*>& Tower::getBullets() {
	return this->bullets;
}
std::string Tower::getBulletType() {
	return this->bulletName;
}
sf::Vector2f Tower::getPosition() {
	return this->position;
}
void Tower::setTarget(Enemy* target) {
	this->target = target;
}

void Tower::updateTarget() {
	float dist = 9999.f;
	Enemy* closest = nullptr;
	for (auto& e : *this->game->getEnemies()) {
		float tmp = std::sqrt(pow(e->getPosition().x - this->position.x, 2) + pow(e->getPosition().y - this->position.y, 2));
		if (tmp <= Global::getUnit().x * radious) {
			if (tmp < dist) {
				dist = tmp;
				closest = e;
				this->enemyPos = closest->getPosition();
			}
		}
	}
	this->setTarget(closest);
}
void Tower::aimAtTarget() {
	this->sprite.setRotation(atan2(target->getPosition().y - this->position.y, target->getPosition().x - this->position.x) * RAD_TO_DEG + 90);
}

void Tower::aimAtMouse() {
	this->sprite.setRotation(atan2(sf::Mouse::getPosition(*Global::window).y - this->position.y, sf::Mouse::getPosition(*Global::window).x - this->position.x) * RAD_TO_DEG + 90);
}
