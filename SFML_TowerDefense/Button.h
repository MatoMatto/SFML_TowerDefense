#pragma once

#include "pch.h"
#include "Input.h"

class Button: public Input {

public:
	Button();
	Button(std::string text, int charSize, sf::Color bg, sf::Color textColor, int outline, sf::Color outlineColor);

};