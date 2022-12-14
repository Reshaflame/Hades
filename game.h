#pragma once

#include "data.h"
#include "map.h"

class Game
{
public:
	Game();
	~Game();

private:
	Map* currentMap;
	Data* data;
};

Game::Game()
{
}

Game::~Game()
{
}