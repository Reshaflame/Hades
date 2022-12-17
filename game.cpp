
#include "game.h"

Game::Game()
{
	currentMap = nullptr;
	data = new Data();
}

Game::~Game()
{
	delete data;
}

Map* Game::addMap(char* m_name)
{
	if (!m_name) return nullptr;
	return data->addMap(m_name);
}

Room* Game::addRoomToData(char* r_name)
{
	if (!r_name) return nullptr;
	return data->addRoom(r_name);
}

Map* Game::addRoomToMap(char* r_name, Direction direction = None)
{
	if (!r_name) return nullptr;
	
	Room* newRoom = data->getRoom(r_name);
	if (!newRoom) return nullptr;
	
	if (!currentMap->addRoom(newRoom, direction)) return nullptr;
	else return currentMap;
}

void Game::printCurrMap()
{
	currentMap->printMap();
}

Map* Game::changeCurrMap(char* m_name)
{
	if (!m_name) return nullptr;

	return data->getMap(m_name);
}
void Game::printData()// prints only maps and rooms names.
{
	data->printData();
}

