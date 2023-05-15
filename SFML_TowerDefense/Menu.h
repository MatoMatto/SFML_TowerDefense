#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Textbox.h"
#include "Globals.h"


class Menu
{
	sf::Vector2f position;
	sf::FloatRect size;
	sf::Font font;
	sf::Sprite logo, background;
public:
	std::vector<Input*> inputs;

	Menu();
	~Menu();
	Menu(const sf::Vector2f position, sf::Texture& texture, sf::Texture& bgTexture);
	void drawTo(sf::RenderTarget& target);
	void setFont(sf::Font& font);

	void addButton(Button* button);
	void addTextBox(Textbox* textbox);

	void centerInputsVertically();

	void update();
};

