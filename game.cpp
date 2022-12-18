
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

Map* Game::CombineCurrMapToMap(char* m_name)
{
	Map* temp_m = data->getMap(m_name);
	if (!temp_m) return nullptr;
	*currentMap += *temp_m;
	return currentMap;
}

// no empty map constructors are pain...
Map* Game::CombineMapsToNew(char* new_m_name, char* m_name)
{
	Map* temp_m = data->getMap(m_name);
	if (!temp_m) return nullptr;


	Map* combined = new Map(new_m_name);

}

void Game::printData()// prints only maps and rooms names.
{
	data->printData();
}

bool Game::addItemToRoom(char* i_name) 
{
	currentMap->addItemToCurrRoom(i_name);
	return true;
}
bool Game::addMonsterToRoom(char* m_name)
{
	currentMap->addMosterToCurrRoom(m_name);
	return true;
}
bool Game::addItemToDataRoom(char* r_name, char* i_name)
{
	data->addItem(r_name, i_name);
	return true;
}
bool Game::addMonsterToDataRoom(char* r_name, char* m_name)
{
	data->addMonster(r_name, m_name);
	return true;
}
void Game::printData()// prints only maps and rooms names.
{
	data->printData();
}
