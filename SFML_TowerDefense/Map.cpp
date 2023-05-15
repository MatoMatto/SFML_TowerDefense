#include "Map.h"
#include "pch.h"

void Map::initTextures() {
	for (std::string e : this->textureNames) {
		sf::Texture* t = new sf::Texture();
		t->loadFromFile("Resources/Sprites/"+e);
		this->textures.push_back(t);
	}
	for (int i = 0; i < 5; i++) {
		sf::Texture* t = new sf::Texture();
		t->loadFromFile("Resources/Sprites/bush_" + std::to_string(i) + ".png");
		this->bushTextures.push_back(t);
	}
}

void Map::initVars() {
	this->textureNames = {"grass.png", "path.png"};
	this->maxBushes = 5;
}

Map::Map() {
	this->initVars();
	this->initTextures();
}

Map::~Map(){
	for (auto& e : this->tiles) {
		delete e;
	}
	for (auto& e : this->textures) {
		delete e;
	}
	for (auto& e : this->bushTextures) {
		delete e;
	}
	for (auto& e : this->bushes) {
		delete e;
	}
	this->tiles.clear();
	this->path.clear();
}

void Map::drawTo(sf::RenderTarget& target) {
	for (auto& e : this->tiles) {
		e->drawTo(target);
	}
	for (auto& e : this->bushes) {
		target.draw(*e);
	}
}

void Map::loadMap(std::string filename) {
	std::fstream fs;
	fs.open("Resources/Maps/" + filename, std::ios::in);
	fs >> start.x >> start.y;
	fs >> end.x >> end.y;
	fs.get();
	char x = 0;
	int i = 0;
	Tile* nt;
	while (!fs.eof()) {
		x = fs.get();
		if (x<'0'||x>'9')continue;
		x -= '0';
		nt = new Tile(*this->textures[x], sf::Vector2f(i % 16, i / 16), x);
		i++;
		this->tiles.push_back(nt);
	}
	this->loadPath();
	this->loadBushes();
}
void Map::loadPath() {
	this->path.clear();
	Tile* startTile = getTile(start.x, start.y);
	Tile* endTile = getTile(end.x, end.y);

	buildPath(startTile, endTile);

	// Add the end tile to the path
	this->path.push_back(endTile);
}

bool Map::buildPath(Tile* current, Tile* endTile) {
	if (current == endTile) {
		// Base case: Reached the end tile
		this->path.push_back(current);
		return true;
	}

	
	if (std::find(this->path.begin(), this->path.end(), current) != this->path.end()) {
		// The current tile is already in the path, indicating a loop
		return false;
	}

	
	this->path.push_back(current);

	std::vector<Tile*> adjacentTiles = getAdjacentTiles(current);
	for (auto& tile : adjacentTiles) {
		if (buildPath(tile, endTile)) {
			return true;
		}
	}

	
	this->path.pop_back();

	return false;
}

void Map::loadBushes() {
	for (int i = 0; i < this->maxBushes; i++) {
		int tile = rand() % (this->tiles.size() - this->path.size());
		int tc = 0;
		for (auto& e : this->tiles) {
			if (e->getType() == Global::Cell::Grass) {
				tc++;
				if (tc == tile) {
					sf::Sprite* s = new sf::Sprite();
					s->setTexture(*this->bushTextures[rand()%this->bushTextures.size()]);
					s->setPosition({ e->getPosition().x + TILE_SIZE / 2, e->getPosition().y + TILE_SIZE / 2 });
					s->setScale({ 64.f / s->getLocalBounds().width,64.f / s->getLocalBounds().height });
					this->bushes.push_back(s);
				}
			}
		}
	}
}

Tile* Map::getTile(int x, int y) const {
	if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT) {
		return nullptr;
	}
	return tiles[x + y * GRID_WIDTH];
}

bool Map::isTraversable(Tile* tile) const {
	return tile->getType() != Global::Cell::Grass;
}


// Returns a vector of Tile objects that are adjacent to the given Tile object
std::vector<Tile*> Map::getAdjacentTiles(Tile* tile) {
	std::vector<Tile*> adjacentTiles;
	sf::Vector2i pos = tile->getIndex();
	int x = pos.x;
	int y = pos.y;

	Tile* topTile = this->getTile(x, y - 1);
	Tile* rightTile = this->getTile(x + 1, y);
	Tile* bottomTile = this->getTile(x, y + 1);
	Tile* leftTile = this->getTile(x - 1, y);
	if (topTile && isTraversable(topTile)) {
		adjacentTiles.push_back(topTile);
	}
	if (rightTile && isTraversable(rightTile)) {
		adjacentTiles.push_back(rightTile);
	}
	if (bottomTile && isTraversable(bottomTile)) {
		adjacentTiles.push_back(bottomTile);
	}
	if (leftTile && isTraversable(leftTile)) {
		adjacentTiles.push_back(leftTile);
	}
	return adjacentTiles;
}


const bool Map::canPlaceTower(sf::Vector2f mousePos) {
	sf::FloatRect tower(mousePos.x - TOWER_SIZE / 2, mousePos.y - TOWER_SIZE / 2, TOWER_SIZE, TOWER_SIZE);
	for (auto& tile : this->path) {
		sf::FloatRect tmpTile(tile->getPosition().x, tile->getPosition().y, TILE_SIZE, TILE_SIZE);
		if (tower.intersects(tmpTile))return false;
	}
	return true;
}

std::vector<Tile*>* Map::getPath() {
	return &this->path;
}