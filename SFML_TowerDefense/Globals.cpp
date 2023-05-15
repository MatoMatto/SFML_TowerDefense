#include "Globals.h"

sf::RenderWindow* Global::window = nullptr;

sf::Vector2f Global::getUnit() {
    return { (Global::window->getSize().x * GAME_SIZE / GRID_WIDTH),(Global::window->getSize().y * GAME_SIZE / GRID_HEIGHT) };
}
