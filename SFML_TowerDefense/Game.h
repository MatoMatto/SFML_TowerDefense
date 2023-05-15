#pragma once
#include "pch.h"
#include "Enemy.h"
#include "Menu.h"
#include "Map.h"
#include "HUD.h"
#include "TowerPlace.h"
#include "Tower.h"
enum GameState {
	PLAYING,
	MENU,
	PAUSED,
	SETTINGS,
	MAP_SELECT
};
class Game
{
private:

	sf::VideoMode videoMode;
	sf::Event ev;

	sf::Vector2i mousePos;
	sf::Vector2f mousePosView;
	sf::Vector2f screen;
	sf::Vector2f velocity;
	sf::Font& font;
	sf::Text uiText;
	sf::Text gameOverText;
	sf::Clock FPSClock, roundClock;
	sf::Texture logoTexture, backgroundTexture, baseTexture;
	std::map<std::string,sf::Texture> enemyTextures, bulletTextures;
	sf::SoundBuffer clickBuffer, enemyDeathBuffer;
	sf::Sound clickSound, enemyDeathSound;

	sf::Music theme;

	std::vector<std::string> enemyTypes;




	std::vector<Enemy*> enemies;
	std::vector<Tower*> towers;
	Menu* menu, *settings, *pauseMenu;
	Map* map;
	HUD* hud;
	TowerPlace* tp;


	float acceleration = 1;
	float max_velocity = 10;
	float FPS;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	bool endGame;
	bool mouseHeld;
	bool showFPS;
	int round;
	unsigned int points;
	unsigned int maxEnemies;
	int health;
	int coins;
	int gameState;
	bool roundPlaying;

	std::vector<std::string> menuText, settingsText, pauseMenuText;
	
	
	unsigned framerate_limit = 144;
	bool v_sync = false;
	std::string windowTitle;

	void initText();
	void initFonts();
	void initVars();
	void initWindow();
	void initMenu();
	void initHUD();
public:
	Game();
	~Game();

	const bool getWindowIsOpen() const;
	const bool getEndGame() const;
	void newGame();
	void spawnEnemy(std::string enemy);
	void pollEvents();
	void updateMousePosition();
	int calculateFPS();
	float getFPS();

	void updateText();
	void updateEnemies();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();

	void run();
	std::vector<Tower*>* getTowers();
	std::vector<Enemy*>* getEnemies();
	TowerPlace* getTowerPlace();
	Map* getMap();
	sf::Texture& getBaseTexture();
	std::map<std::string, sf::Texture>* getEnemyTextures();
	std::map<std::string,sf::Texture>* getBulletTextures();
	int* money();
	void saveSettings();
};

