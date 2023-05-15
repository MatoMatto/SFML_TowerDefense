#include "Game.h"

void Game::initText(){
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(12);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setOutlineColor(sf::Color::Black);
	this->uiText.setOutlineThickness(2);
	this->uiText.setString("Hello");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setString("Game over");
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setOutlineColor(sf::Color::White);
	this->gameOverText.setOutlineThickness(5);
	this->gameOverText.setCharacterSize(MENU_FONT_HEIGHT * 2);
	this->gameOverText.setOrigin(sf::Vector2f( this->gameOverText.getLocalBounds().width / 2, this->gameOverText.getLocalBounds().height / 2 ));
	this->gameOverText.setPosition(sf::Vector2f( Global::window->getSize().x / 2, Global::window->getSize().y / 2 ));
}
void Game::initFonts(){
	this->font = FontLoader::getInstance().getFont();
}
void Game::initVars(){
	this->videoMode.height = WIN_HEIGHT;
	this->videoMode.width = WIN_WIDTH;
	Global::window = nullptr;
	this->points = 0;
	this->enemySpawnTimerMax = 5.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->gameState = GameState::MENU;
	this->maxEnemies = 0;
	this->mouseHeld = false;
	this->health = 100;
	this->coins = 300;
	this->endGame = true;
	this->roundPlaying = false;
	this->round = 1;
	this->logoTexture.loadFromFile("Resources/Sprites/logo.png");
	this->backgroundTexture.loadFromFile("Resources/Sprites/main_background.png");

	this->menuText.push_back("Play");
	this->menuText.push_back("Settings");
	this->menuText.push_back("Exit");
	
	this->settingsText.push_back("FPS: ");
	this->settingsText.push_back("Vsync: ");
	this->settingsText.push_back("Back");

	this->pauseMenuText.push_back("Resume");
	this->pauseMenuText.push_back("Settings");
	this->pauseMenuText.push_back("Return to menu");

	this->clickBuffer.loadFromFile("Resources/Sounds/click.wav");
	this->clickSound.setBuffer(this->clickBuffer);

	this->enemyDeathBuffer.loadFromFile("Resources/Sounds/death.ogg");
	this->enemyDeathSound.setBuffer(this->enemyDeathBuffer);

	
	this->baseTexture.loadFromFile("Resources/Sprites/base.png");

	this->theme.openFromFile("Resources/Sounds/theme.wav");
	this->theme.setVolume(10.f);
	this->theme.play();

	std::fstream fs;
	std::string tmp;
	fs.open("Resources/config/bullets.ini", std::ios::in);
	while (std::getline(fs, tmp)) {
		this->bulletTextures[tmp] = (std::move(sf::Texture()));
		this->bulletTextures[tmp].loadFromFile("Resources/Sprites/" + tmp + ".png");
	}
	fs.close();
	fs.open("Resources/config/enemies.ini", std::ios::in);
	while (std::getline(fs, tmp)) {
		enemyTypes.push_back(tmp);
		this->enemyTextures[tmp] = (std::move(sf::Texture()));
		this->enemyTextures[tmp].loadFromFile("Resources/Sprites/" + tmp + ".png");
	}
	fs.close();
}

void Game::initWindow(){

	std::ifstream ifs("Resources/config/settings.ini");
	this->windowTitle = "My Window";
	this->framerate_limit = 144;
	this->v_sync = false;
	if (ifs.is_open()) {
		std::getline(ifs, this->windowTitle);
		ifs >> this->videoMode.width >> this->videoMode.height;
		ifs >> framerate_limit;
		ifs >> v_sync;
		ifs >> this->showFPS;
	}
	ifs.close();
	Global::window = new sf::RenderWindow(this->videoMode, this->windowTitle, sf::Style::Titlebar | sf::Style::Close);
	if(!v_sync)Global::window->setFramerateLimit(framerate_limit);
	Global::window->setVerticalSyncEnabled(v_sync);
	
}

void Game::initMenu() {
	this->menu = new Menu(sf::Vector2f(this->videoMode.width / 2, this->videoMode.height / 2), logoTexture, this->backgroundTexture);
	this->settings = new Menu(sf::Vector2f(this->videoMode.width / 2, this->videoMode.height / 2), logoTexture, this->backgroundTexture);
	this->pauseMenu = new Menu(sf::Vector2f(this->videoMode.width / 2, this->videoMode.height / 2), logoTexture, this->backgroundTexture);
	//Title text
	Textbox* tb = new Textbox();
	tb->setFontSize(MENU_FONT_HEIGHT);
	tb->setFont(this->font);
	tb->setText("Settings");
	tb->setBackgroundColor(sf::Color::Transparent);
	tb->setHoverColor(sf::Color::Transparent);
	tb->setPadding({ 0,0,0,0 });
	tb->setMargin({ 0,50,0,0 });
	this->settings->addTextBox(tb);
	//Add buttons

	for (int i = 0; i < menuText.size(); i++) {
		Button* btn = new Button();
		btn->setFont(this->font);
		btn->setText(this->menuText[i]);
		btn->setTextColor(sf::Color::Black);
		btn->setFontSize(MENU_FONT_HEIGHT);
		btn->setBackgroundColor(sf::Color(255, 255, 255, 127));
		btn->setHoverColor(sf::Color(255, 255, 255, 200));
		btn->setOutlineColor(sf::Color(128, 83, 0, 255));
		btn->setOutlineThickness(2);
		btn->setPadding({ 10,10,5,5 });
		btn->setMargin({ 10, 10, 0,0 });
		this->menu->addButton(btn);
	}
	for (int i = 0; i < settingsText.size(); i++) {
		Button* btn = new Button();
		btn->setFont(this->font);
		if (i == 0) {
			btn->setText(this->settingsText[i]+((this->showFPS)?"ON":"OFF"));
		}
		else if (i == 1) {
			btn->setText(this->settingsText[i] + ((this->v_sync) ? "ON" : "OFF"));
		}else btn->setText(this->settingsText[i]);
		btn->setTextColor(sf::Color::Black);
		btn->setFontSize(MENU_FONT_HEIGHT);
		btn->setBackgroundColor(sf::Color(255, 255, 255, 127));
		btn->setHoverColor(sf::Color(255, 255, 255, 200));
		btn->setOutlineColor(sf::Color(128, 83, 0, 255));
		btn->setOutlineThickness(2);
		btn->setPadding({ 10,10,5,5 });
		btn->setMargin({ 10, 10, 0,0 });
		this->settings->addButton(btn);
	}
	for (int i = 0; i < this->pauseMenuText.size(); i++) {
		Button* btn = new Button();
		btn->setFont(this->font);
		btn->setText(this->pauseMenuText[i]);
		btn->setTextColor(sf::Color::Black);
		btn->setFontSize(MENU_FONT_HEIGHT);
		btn->setBackgroundColor(sf::Color(255, 255, 255, 127));
		btn->setHoverColor(sf::Color(255, 255, 255, 200));
		btn->setOutlineColor(sf::Color(128, 83, 0, 255));
		btn->setOutlineThickness(2);
		btn->setPadding({ 10,10,5,5 });
		btn->setMargin({ 10, 10, 0,0 });
		this->pauseMenu->addButton(btn);
	}


	this->settings->centerInputsVertically();
	this->menu->centerInputsVertically();
	this->pauseMenu->centerInputsVertically();

}
Game::Game() : font(FontLoader::getInstance().getFont()) {
	this->initVars();
	this->initWindow();
	this->initMenu();
	this->initHUD();
	this->initFonts();
	this->initText();
}
Game::~Game() {
	delete Global::window;
	delete this->menu;
	delete this->settings;
	delete this->pauseMenu;
	delete this->map;
	delete this->tp;
	for (auto& e : this->enemies) {
		delete e;
	}
	for (auto& e : this->towers) {
		delete e;
	}
}

const bool Game::getWindowIsOpen() const{
	return Global::window->isOpen();
}



void Game::spawnEnemy(std::string enemy){
	Enemy* en = new Enemy(&this->font, this, enemy);
	en->setPath(this->map->getPath());
	en->setTarget({ this->map->getPath()->at(0)->getPosition().x + (Global::getUnit().x / 2),  this->map->getPath()->at(0)->getPosition().y + (Global::getUnit().y / 2) });
	this->enemies.push_back(en);
}



void Game::pollEvents(){
	while (Global::window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			Global::window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Up)this->maxEnemies++;
			else if (ev.key.code == sf::Keyboard::Down) { 
				if (this->maxEnemies) { 
					this->maxEnemies--; 
					if (this->maxEnemies < this->enemies.size()) { 
						delete this->enemies.at(this->enemies.size() - 1);
						this->enemies.pop_back(); 
					}
				} 
			}
			else if (ev.key.code == sf::Keyboard::Escape) {
				if (this->gameState == GameState::PLAYING)this->gameState = GameState::PAUSED;
				else if (this->gameState == GameState::PAUSED && !this->endGame)this->gameState = GameState::PLAYING;
				else if (this->gameState == GameState::SETTINGS && !this->endGame)this->gameState = GameState::PAUSED;
				else if(this->gameState != GameState::MENU){ 
					this->gameState = GameState::MENU; 
					this->theme.play();
				}
			}
			break;
		case sf::Event::MouseButtonPressed:
			
			if (this->gameState == GameState::MENU) {
				for (auto& e : this->menu->inputs) {
					if (e->isMouseOver(*Global::window)) {
						this->clickSound.play();
						if (e->getText() == "Play") {
							this->newGame();
							this->theme.pause();
						}
						else if (e->getText() == "Settings") {
							this->gameState = GameState::SETTINGS;
						}
						else if (e->getText() == "Exit") {
							Global::window->close();
						}
					}
				}
			}
			else if (this->gameState == GameState::SETTINGS) {
				for (auto& e : this->settings->inputs) {
					if (e->isMouseOver(*Global::window)) {
						this->clickSound.play();
						if (e->getText().find("FPS") != std::string::npos) {
							this->showFPS = !this->showFPS;
							if (this->showFPS)e->setText("FPS: ON");
							else e->setText("FPS: OFF");
							e->setPadding(e->getPadding());
						}
						else if (e->getText().find("Vsync") != std::string::npos) {
							this->v_sync = !this->v_sync;
							if (this->v_sync)e->setText("Vsync: ON");
							else e->setText("Vsync: OFF");
							e->setPadding(e->getPadding());
						}
						else if (e->getText() == "Back") {
							if (!this->endGame)this->gameState = GameState::PAUSED;
							else this->gameState = GameState::MENU;
							this->saveSettings();
						}
					}
				}
			}
			else if (this->gameState == GameState::PAUSED) {
				for (auto& e : this->pauseMenu->inputs) {
					if (e->isMouseOver(*Global::window)) {
						this->clickSound.play();
						if (e->getText() == "Resume") {
							this->gameState = GameState::PLAYING;
						}
						else if (e->getText() == "Settings") {
							this->gameState = GameState::SETTINGS;
						}
						else if (e->getText() == "Return to menu") {
							this->gameState = GameState::MENU;
							this->theme.play();
						}
					}
				}
			}
			else if (this->gameState == GameState::PLAYING && !this->endGame) {
				hud->handleClickEvent(ev);
				tp->click();
			}
			break;
		}
	}
}

void Game::updateMousePosition(){
	this->mousePos = sf::Mouse::getPosition(*Global::window);
	this->mousePosView = Global::window->mapPixelToCoords(this->mousePos);
}

int Game::calculateFPS() {
	return 1.f/FPSClock.restart().asSeconds();
}

void Game::updateText(){
	std::stringstream ss;
	if (this->showFPS) {
		ss << "FPS: " << this->FPS<<std::endl;
	}
	ss << "Enemies: "<<this->maxEnemies;
	this->uiText.setString(ss.str());
}


void Game::updateEnemies(){
	//spawn timer

	if (!maxEnemies && roundClock.getElapsedTime().asSeconds() > 5.f) {
		round++;
		maxEnemies += round + round/10;
		enemySpawnTimerMax *= 1.f - round / 5;
		enemySpawnTimerMax = std::max(enemySpawnTimerMax, 0.5f);
	}
	if (this->enemies.size() < this->maxEnemies) {
		std::string enemy;
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax * this->FPS) {
			if (round <= 3) {
				enemy = enemyTypes[0];
			}
			else {
				enemy = enemyTypes[rand() % enemyTypes.size()];
			}
			this->spawnEnemy(enemy);
			this->enemySpawnTimer = 0.f;
		}
		else this->enemySpawnTimer += 1.f;
	}
	for (int i = 0; i < this->enemies.size(); i++) {
		if (this->enemies[i]->reachedEnd()) { 
			health--; 
			this->enemies.erase(enemies.begin() + i--);
			this->maxEnemies--;
			roundClock.restart();
			continue;
		}
		if (this->enemies[i]->isDead()) {
			this->enemies.erase(enemies.begin() + i--);
			this->coins += 50;
			this->maxEnemies--;
			this->enemyDeathSound.play();
			roundClock.restart();
			continue;
		}


		//move enemies
		//this->enemies[i].setTarget(mousePosView);
		this->enemies[i]->update(this->FPS);
	}
}

const bool Game::getEndGame() const{
	return this->endGame;
}


void Game::update(){
	this->pollEvents();
	this->FPS = this->calculateFPS();
	if (this->gameState == GameState::MENU)this->menu->update();
	else if (this->gameState == GameState::SETTINGS)this->settings->update();
	else if (this->gameState == GameState::PAUSED)this->pauseMenu->update();
	if (!this->endGame && this->gameState == GameState::PLAYING) {
		this->updateMousePosition();
		this->updateText();
		this->updateEnemies();
		this->hud->update();
		this->tp->update();
		for (auto& e : this->towers) {
			e->update();
		}
	}
	if (this->health <= 0)this->endGame = true;
}

void Game::renderText(sf::RenderTarget& target) {
	target.draw(this->uiText);
	if(this->gameState == GameState::PLAYING && this->endGame)target.draw(this->gameOverText);
}

void Game::renderEnemies(sf::RenderTarget& target){
	for (auto& e : this->enemies) {
		e->draw(target);
	}
}

void Game::initHUD() {
	this->hud = new HUD(&health, &coins, this);
	hud->setTowerPickerButtonPosition();
	this->tp = new TowerPlace(this);
}

void Game::render(){
	Global::window->clear();
	if (this->gameState == GameState::PLAYING) {
		this->map->drawTo(*Global::window);
		this->hud->drawTo(*Global::window);
		for (auto& e : this->towers) {
			e->draw(*Global::window);
		}
		this->tp->drawTo(*Global::window);
		this->renderEnemies(*Global::window);
		this->renderText(*Global::window);
	}
	if (this->gameState == GameState::MENU)this->menu->drawTo(*Global::window);
	else if (this->gameState == GameState::SETTINGS)this->settings->drawTo(*Global::window);
	else if (this->gameState == GameState::PAUSED)this->pauseMenu->drawTo(*Global::window);
	Global::window->display();
}

void Game::run() {
	
	while (Global::window->isOpen()) {
		this->update();
		this->render();
	}
}

float Game::getFPS() {
	return this->FPS;
}

void Game::newGame() {
	this->map = new Map();
	this->gameState = GameState::PLAYING;
	this->endGame = false;
	std::string map = "demo1.tdmap";
	this->health = 10;
	this->coins = 900;
	this->round = 1;
	std::fstream fs;
	fs.open("Resources/config/game.ini", std::ios::in);
	std::getline(fs, map);
	fs >> this->coins;
	fs >> this->health;
	fs >> this->round;
	this->map->loadMap(map);
	fs.close();


	this->enemySpawnTimer = 0;
	this->roundClock.restart();
	for (auto& e : this->enemies) {
		delete e;
	}
	for (auto& e : this->towers) {
		delete e;
	}
	this->enemies.clear();
	this->towers.clear();
}

std::vector<Tower*>* Game::getTowers() {
	return &this->towers;
}

void Game::saveSettings() {
	std::fstream fs;
	fs.open("Resources/config/settings.ini", std::ios::out);
	fs << this->windowTitle << std::endl;
	fs << this->videoMode.width << " " << this->videoMode.height << std::endl;
	fs << this->framerate_limit << std::endl;
	fs << this->v_sync << std::endl;
	fs << this->showFPS;
	fs.close();
}

std::vector<Enemy*>* Game::getEnemies() {
	return &this->enemies;
}

TowerPlace* Game::getTowerPlace() {
	return this->tp;
}

Map* Game::getMap() {
	return this->map;
}

int* Game::money() {
	return &this->coins;
}

sf::Texture& Game::getBaseTexture() {
	return this->baseTexture;
}

std::map<std::string,sf::Texture>* Game::getBulletTextures() {
	return &this->bulletTextures;
}

std::map<std::string,sf::Texture>* Game::getEnemyTextures() {
	return &this->enemyTextures;
}
