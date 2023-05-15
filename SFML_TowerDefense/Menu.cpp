#include "Menu.h"
#include "pch.h"

Menu::Menu(){
	
}

Menu::~Menu(){
	for (auto e : this->inputs) {
		delete e;
	}
	this->inputs.clear();
}

Menu::Menu(const sf::Vector2f position, sf::Texture& texture, sf::Texture& bgTexture){
	this->position = position;
	this->setFont(FontLoader::getInstance().getFont());
	this->logo.setTexture(texture);
	this->background.setTexture(bgTexture);
	this->background.setScale(
		Global::window->getSize().x / this->background.getLocalBounds().width,
		Global::window->getSize().y / this->background.getLocalBounds().height
	);
}

void Menu::drawTo(sf::RenderTarget& target){
	target.draw(this->background);
	target.draw(this->logo);
	for (auto e : this->inputs) {
		e->drawTo(target);
	}

}

void Menu::setFont(sf::Font& font){
	//this->font.loadFromFile("Resources/Fonts/OETZTYP_.TTF");
	this->font = font;
}

void Menu::addButton(Button* button){
	this->inputs.push_back(button);
	this->centerInputsVertically();
}
void Menu::addTextBox(Textbox* textbox) {
	this->inputs.push_back(textbox);
	this->centerInputsVertically();
}
void Menu::centerInputsVertically() {
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

void Menu::update(){
	for (auto& e : this->inputs) {
		e->update();
	}
}
