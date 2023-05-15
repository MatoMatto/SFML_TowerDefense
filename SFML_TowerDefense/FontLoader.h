#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class FontLoader
{
	FontLoader();
	sf::Font m_font;
public:
	static FontLoader& getInstance();
	sf::Font& getFont();
};

