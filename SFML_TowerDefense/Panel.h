#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Textbox.h"
class Panel : public sf::Drawable, public sf::Transformable {
	std::vector<Button*> buttons;
	std::vector<Textbox*> textboxes;
	sf::Vector2f size;
	sf::Vector2f position;
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void centerInputsVertically();
	void centerInputsHorizontally();
	Panel();
};

