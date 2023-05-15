#include "TowerPlace.h"
#include "Game.h"
TowerPlace::TowerPlace(Game* game) {
    this->game = game;
    this->price = 0;
    this->radius = Global::getUnit().x * 3;
    this->gameTowers = this->game->getTowers();
    bool placing = false;
}

void TowerPlace::click() {
    if (!placing)return;
    if (this->canPlace() && *this->game->money() >= price) {
        Tower* nt = new Tower(this->name, this->position, game, *this->texture);
        this->gameTowers->push_back(nt);
        *this->game->money() -= price;
        this->placing = false;
    }
}

bool TowerPlace::canPlace() {
    sf::FloatRect placer;
    placer.height = placer.width = TOWER_SIZE;
    placer.top = this->position.y - TOWER_SIZE / 2;
    placer.left = this->position.x - TOWER_SIZE / 2;

    for (auto& e : *this->game->getMap()->getPath()) {
        if (placer.intersects(sf::FloatRect(e->getPosition(), Global::getUnit()))) {
            return false;
        }
    }
    if (!(placer.top >= 0 && placer.top + placer.height <= Global::getUnit().y * GRID_HEIGHT && placer.left >= 0 && placer.left + placer.width <= Global::getUnit().x * GRID_WIDTH))return false;
    for (auto& e : *this->game->getTowers()) {
        sf::FloatRect tow;
        tow.height = tow.width = TOWER_SIZE;
        tow.top = e->getPosition().y - TOWER_SIZE / 2;
        tow.left = e->getPosition().x - TOWER_SIZE / 2;
        if (tow.intersects(placer))return false;
    }
    return true;
}

void TowerPlace::update() {
    this->position = (sf::Vector2f)sf::Mouse::getPosition(*Global::window);
    this->sprite.setPosition(this->position);
    this->range.setPosition(this->position);

    if (this->canPlace()) {
        this->range.setFillColor(sf::Color(0x33, 0x33, 0x33, 127));
    }
    else {
        this->range.setFillColor(sf::Color(255, 0, 0, 127));
    }
}

void TowerPlace::drawTo(sf::RenderTarget& target) {
    if (placing) {
        target.draw(range);
        target.draw(sprite);
    }
}

void TowerPlace::setTexture(sf::Texture& texture) {
    this->sprite.setTexture(texture);
    this->sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    this->sprite.setScale({ TOWER_SIZE / this->sprite.getLocalBounds().width,TOWER_SIZE / this->sprite.getLocalBounds().height });

    this->range.setRadius(radius);
    this->range.setOrigin(radius, radius);
    this->range.setPosition(sprite.getPosition());
    this->range.setFillColor(sf::Color(255, 255, 255, 50));
    this->range.setOutlineThickness(1);
    this->range.setOutlineColor(sf::Color::Red);
}

void TowerPlace::setTower(std::string tower, sf::Texture& texture) {
    this->placing = true;
    this->name = tower;
    this->texture = &texture;
    
    std::fstream fs;
    fs.open("Resources/Towers/" + tower + ".txt", std::ios::in);
    fs >> price;
    fs >> shootDelay;
    fs >> radius;
    fs.close();
    radius *= Global::getUnit().x;
    this->setTexture(texture);
}

void TowerPlace::reset() {
    this->placing = false;
    this->radius = Global::getUnit().x * 3;
}
