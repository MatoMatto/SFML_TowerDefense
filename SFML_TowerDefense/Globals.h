#pragma once
#ifndef GLOBALS
#define GLOBALS
#include <SFML/Graphics.hpp>
constexpr double RAD_TO_DEG = (180 / 3.14159265358979323846);
constexpr unsigned short WIN_HEIGHT = 720;
constexpr unsigned short WIN_WIDTH = 1280;

constexpr unsigned char TILE_SIZE = 32;
constexpr unsigned char FONT_HEIGHT = 16;
constexpr unsigned char MENU_FONT_HEIGHT = 25;

constexpr unsigned char TOWER_SIZE = 80;
constexpr unsigned char GRID_WIDTH = 16;
constexpr unsigned char GRID_HEIGHT = 9;
constexpr float GAME_SIZE = 0.85f;

const char DEFAULT_FONT[] = "Resources/Fonts/OETZTYP_.TTF";


namespace Global {
	enum Cell {
		Grass = 0,
		Path
	};
	extern sf::RenderWindow* window;
	sf::Vector2f getUnit();
}

#endif // GLOBALS
