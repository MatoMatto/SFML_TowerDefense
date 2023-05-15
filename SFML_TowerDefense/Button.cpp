#include "Button.h"

Button::Button() {}
Button::Button(std::string text, int charSize, sf::Color bg, sf::Color textColor, int outline, sf::Color outlineColor) {
	this->textbox.setString(text);
	this->textbox.setFillColor(textColor);
	this->textbox.setCharacterSize(charSize);
	this->charHeight = charSize;
	this->rect.setFillColor(bg);
	this->rect.setOutlineColor(outlineColor);
	this->rect.setOutlineThickness(outline);

}
