#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Input.h"
#define BACKSPACE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27


class Textbox: public Input {

	std::ostringstream text;
	bool isSelected = false;
	bool isSelectable = false;
	bool hasLimit = false;
	int limit = 5;

	void inputLogic(int charTyped);
	void deleteLastChar();
public:
	Textbox();
	Textbox(int size, sf::Color color, bool selected);
	Textbox(int size, sf::Color color, bool selected, std::string defaultText);
	void setLimit(bool bLimit);
	void setLimit(bool bLimit, int limit);
	void setSelected(bool sel);
	void setSelectable(bool sel);
	std::string getText();
	void typedOn(sf::Event input);
	void setFontSize(int size)override;
};