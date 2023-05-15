#include "Panel.h"

void Panel::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
	
}
/*
void Panel::centerInputsVertically() {
	// Calculate the total height of all the buttons
	float totalHeight = 0.0f;
	for (auto& input : inputs) {
		totalHeight += input->getFullSize().height;
	}

	// Calculate the vertical offset for the logo sprite and the buttons
	float offsetY = (Global::window->getSize().y - totalHeight - logo.getGlobalBounds().height) / 1.5f;

	// Set the position of the logo sprite
	sf::FloatRect logoBounds = logo.getGlobalBounds();
	float logoX = (Global::window->getSize().x - logoBounds.width) / 2.0f;
	logo.setPosition(logoX, offsetY);

	// Set the position of the buttons
	float buttonY = offsetY + logoBounds.height / 1.25f;
	for (auto& input : inputs) {
		sf::FloatRect inputBounds = input->getFullSize();
		float inputX = (Global::window->getSize().x - inputBounds.width) / 2.0f;
		input->setPosition(sf::Vector2f(inputX, buttonY));
		buttonY += inputBounds.height;
	}
}

void Panel::centerInputsHorizontally() {
	// Calculate the total width of all the buttons
	float totalHeight = 0.0f;
	for (auto& input : inputs) {
		totalHeight += input->getFullSize().height;
	}

	// Calculate the vertical offset for the logo sprite and the buttons
	float offsetY = (Global::window->getSize().y - totalHeight - logo.getGlobalBounds().height) / 1.5f;

	// Set the position of the logo sprite
	sf::FloatRect logoBounds = logo.getGlobalBounds();
	float logoX = (Global::window->getSize().x - logoBounds.width) / 2.0f;
	logo.setPosition(logoX, offsetY);

	// Set the position of the buttons
	float buttonY = offsetY + logoBounds.height / 1.25f;
	for (auto& input : inputs) {
		sf::FloatRect inputBounds = input->getFullSize();
		float inputX = (Global::window->getSize().x - inputBounds.width) / 2.0f;
		input->setPosition(sf::Vector2f(inputX, buttonY));
		buttonY += inputBounds.height;
	}
}
*/
Panel::Panel() {

}
