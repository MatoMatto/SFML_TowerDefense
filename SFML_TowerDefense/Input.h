#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "FontLoader.h"
struct Vector4i {
	int top, bottom, left, right;
};

class Input{
protected:
	int charHeight = 20;
	int outlineWidth = 0;
	std::string text;
	sf::Color outlineColor;
	sf::Color fillColor;
	sf::Color hoverColor;
	sf::Text textbox;
	Vector4i padding = { 0,0,0,0 }; //gor, dol, levo, desno
	Vector4i margin = { 0,0,0,0 };
	sf::Sprite image;
	sf::Vector2f position;
	sf::RectangleShape rect;
	unsigned char flags = 0;
	void setSize(sf::FloatRect size);
public:
	Input() {};
	Input(int charSize);
	void setFont(sf::Font& font);
	virtual void setFontSize(int size);
	void setBackgroundColor(sf::Color color);
	void setOutlineColor(sf::Color color);
	void setOutlineThickness(int x);
	void setTextColor(sf::Color color);
	virtual void setPosition(sf::Vector2f pos);
	void setHoverColor(sf::Color color);
	void drawTo(sf::RenderTarget& window);
	bool isMouseOver(sf::RenderWindow& window);
	void setMargin(Vector4i mar);
	void setPadding(Vector4i pad);
	void setText(std::string text);
	void setFlags(char flags);
	void setTexture(sf::Texture& texture);
	void setImageSize(sf::Vector2f size);
	void setTextOutlineColor(sf::Color color);
	void setTextOutlineWidth(int w);
	std::string getText();
	void update();
	Vector4i getMargin();
	Vector4i getPadding();
	sf::FloatRect getSize();
	sf::FloatRect getFullSize();
	sf::Vector2f getPosition();
};

