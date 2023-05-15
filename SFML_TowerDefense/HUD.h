#pragma once
#include <SFML/Graphics.hpp>
#include "Input.h"
#include "Textbox.h"
#include "Button.h"
#include "FontLoader.h"
#include <map>
#include <functional>
constexpr auto TOWER_BUTTON_GAP = 5.0f;
class Game;
class HUD {
	std::vector<Input*> towers;
	std::vector<sf::Texture*> textures;
	std::vector<sf::Text> prices;
	std::vector<int> prc;

	std::map<int, std::function<std::string()>> buttonFunctions;

	Button play;
	int* health, * coins;
	sf::RectangleShape sidePanel, bottomPanel;
	sf::Text coinText, healthText, nameText;
	Game* game;
public:
	HUD(int* health, int *coins, Game* game);

	void drawTo(sf::RenderTarget& target);
	void update();
	void centerText();
	void addButton(Button* btn);
	void addTextbox(Textbox* textbox);
	void setTowerPickerButtonPosition();
	std::vector<Input*>* getButtons();

	void handleClickEvent(sf::Event& ev);
	HUD();
	~HUD();
};

