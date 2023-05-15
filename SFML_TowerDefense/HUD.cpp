#include "HUD.h"
#include "Game.h"

void HUD::addButton(Button* btn) {
	this->towers.push_back(btn);
}
void HUD::addTextbox(Textbox* textbox) {
	this->towers.push_back(textbox);
}
void HUD::setTowerPickerButtonPosition() {
	float x = this->sidePanel.getPosition().x + this->sidePanel.getLocalBounds().width / 2;
	float y = this->sidePanel.getLocalBounds().height / 5.f;

	float totalHeight = this->sidePanel.getLocalBounds().height / 2.f;
	float elementHeight = totalHeight / (this->towers.size() + (this->towers.size() % 2));

	float currentY = y;

	for (size_t i = 0; i < this->towers.size(); i++) {
		Input* tower = this->towers[i];
		tower->setPosition({ x - tower->getSize().width / 2.f, currentY});
		currentY += elementHeight;

		this->prices.at(i).setPosition(x - this->prices.at(i).getLocalBounds().width / 2, currentY);
			
		currentY += (elementHeight + TOWER_BUTTON_GAP) - this->prices.at(i).getLocalBounds().height;
		
	}
}
std::vector<Input*>* HUD::getButtons() {
	return &this->towers;
}
void HUD::handleClickEvent(sf::Event& ev) {
	if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) {
		for (int i = 0; i < towers.size(); i++) {
			if (this->towers[i]->isMouseOver(*Global::window)) {
				if (prc[i] > *coins)std::cout << "Not enaugh money!" << std::endl;
				else {
					this->game->getTowerPlace()->setTower(buttonFunctions[i](), *this->textures[i]);
				}
			}
		}
	}
}
HUD::HUD() {
	this->health = nullptr;
	this->coins = nullptr;
}
HUD::~HUD() {
	for (auto& e : this->towers) {
		delete e;
	}
	for (auto& e : this->textures) {
		delete e;
	}
	this->towers.clear();
	this->textures.clear();
}

HUD::HUD(int* health, int* coins, Game* game){
	this->health = health;
	this->coins = coins;
	this->game = game;
	this->sidePanel.setPosition( {Global::getUnit().x * GRID_WIDTH, 0});
	this->sidePanel.setSize({ Global::window->getSize().x * (1 - GAME_SIZE), (float)Global::window->getSize().y });
	this->bottomPanel.setPosition({0, Global::getUnit().y * GRID_HEIGHT});
	this->bottomPanel.setSize({ (float)Global::window->getSize().x * GAME_SIZE, Global::window->getSize().y * (1 - GAME_SIZE) });

	this->sidePanel.setFillColor(sf::Color(0x55,0x55,0x55));
	this->bottomPanel.setFillColor(sf::Color(0x55, 0x55, 0x55));

	this->coinText.setFont(FontLoader::getInstance().getFont());
	this->healthText.setFont(FontLoader::getInstance().getFont());
	this->nameText.setFont(FontLoader::getInstance().getFont());

	this->coinText.setOutlineColor(sf::Color::Black);
	this->healthText.setOutlineColor(sf::Color::Black);
	this->nameText.setOutlineColor(sf::Color::Black);

	this->coinText.setOutlineThickness(4);
	this->healthText.setOutlineThickness(4);
	this->nameText.setOutlineThickness(4);


	this->nameText.setString("Matic Travnikar, R3A");
	this->nameText.setPosition((this->bottomPanel.getPosition().x + this->bottomPanel.getLocalBounds().width - this->nameText.getLocalBounds().width) / 2, this->bottomPanel.getPosition().y + (this->bottomPanel.getLocalBounds().height - this->nameText.getLocalBounds().height) / 2);

	std::vector<std::string> towerNames;
	std::string tmp;
	std::fstream cf;
	cf.open("Resources/config/towers.ini", std::ios::in);
	while (std::getline(cf, tmp))towerNames.push_back(tmp);
	cf.close();
	for (int i = 0; i < towerNames.size(); i++) {
		sf::Texture* t = new sf::Texture();
		if (!t->loadFromFile("Resources/Sprites/" + towerNames[i] + ".png"))std::cout << "Can't load " << towerNames[i] << std::endl;
		this->textures.push_back(std::move(t));
		Button* btn = new Button();
		btn->setFont(FontLoader::getInstance().getFont());
		btn->setTexture(*this->textures[i]);
		btn->setTextColor(sf::Color::Black);
		btn->setFontSize(MENU_FONT_HEIGHT);
		btn->setBackgroundColor(sf::Color(255, 255, 255, 127));
		btn->setHoverColor(sf::Color(255, 255, 255, 200));
		btn->setOutlineColor(sf::Color(128, 83, 0, 255));
		btn->setOutlineThickness(2);
		btn->setPadding({ 0,0,0,0 });
		btn->setMargin({ 0,0,0,0 });
		this->addButton(btn);
		std::fstream fs;
		fs.open("Resources/Towers/" + towerNames[i] + ".txt");
		int price;
		fs >> price;
		sf::Text tx;
		tx.setFont(FontLoader::getInstance().getFont());
		tx.setOutlineColor(sf::Color::Black);
		tx.setOutlineThickness(4);
		tx.setCharacterSize(MENU_FONT_HEIGHT);
		tx.setString("$"+std::to_string(price));
		this->prices.push_back(std::move(tx));
		this->prc.push_back(price);
		buttonFunctions[i] = [towerNames, i]() {std::cout << towerNames[i] << std::endl; return towerNames[i]; };
	}
	this->setTowerPickerButtonPosition();
}

void HUD::drawTo(sf::RenderTarget& target) {
	target.draw(this->sidePanel);
	target.draw(this->bottomPanel);
	target.draw(this->coinText);
	target.draw(this->healthText);
	target.draw(this->nameText);
	for (auto& e : this->towers) {
		e->drawTo(target);
	}
	for (auto& e : this->prices) {
		target.draw(e);
	}
}

void HUD::update() {
	this->coinText.setString("$" + std::to_string(*coins));
	this->healthText.setString(std::to_string(*health) + " HP");
	this->centerText();
	for (int i = 0; i < towers.size(); i++) {
		if (!this->towers[i]->isMouseOver(*Global::window)) {
			if (*coins >= this->prc[i]) {
				this->towers[i]->setBackgroundColor(sf::Color(255, 255, 255, 127));
				this->towers[i]->setHoverColor(sf::Color(255, 255, 255, 200));
			}
			else {
				this->towers[i]->setBackgroundColor(sf::Color(255, 0, 0, 127));
				this->towers[i]->setHoverColor(sf::Color(255, 0, 0, 200));
			}
		}
		this->towers[i]->update();
	}
}

void HUD::centerText() {
	float y = 50;
	this->coinText.setPosition({ this->sidePanel.getPosition().x + ((this->sidePanel.getLocalBounds().width - this->coinText.getLocalBounds().width) / 2),y });
	y += this->coinText.getLocalBounds().height + 20;
	this->healthText.setPosition({ this->sidePanel.getPosition().x + ((this->sidePanel.getLocalBounds().width - this->coinText.getLocalBounds().width) / 2),y });
}
