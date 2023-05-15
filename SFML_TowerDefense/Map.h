#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_map>
#include "Tile.h"
const sf::Vector2i DIRECTIONS[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

class Map{
	std::vector<Tile*> tiles;
	std::vector<Tile*> path;

	sf::Vector2i start, end;
	std::vector<sf::Texture*> textures;
	std::vector<sf::Texture*> bushTextures;
	std::vector<std::string> textureNames;
	sf::Texture grassTexture, pathTexture;
	
	
	std::vector<sf::Sprite*> bushes;
	int maxBushes;


	void initTextures();
	void initVars();
	
public:
	Map();
	~Map();

	void drawTo(sf::RenderTarget& target);
	void loadMap(std::string filename);
	void loadPath();
	bool buildPath(Tile* current, Tile* endTile);
	const bool canPlaceTower(sf::Vector2f mousePos);
	void loadBushes();
	Tile* getTile(int x, int y) const;
	std::vector<Tile*> getAdjacentTiles(Tile* tile);
	bool isTraversable(Tile* tile) const;
	std::vector<Tile*>* getPath();
};

