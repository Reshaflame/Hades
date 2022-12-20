#pragma once

#include "data.h"
#include "map.h"

class Game
{
public:

	// Almog:
	Game();
	~Game();
	
	// Almog:
	Map* addMap(char* m_name);
	Room* addRoomToData(char* r_name);
	Map* addRoomToMap(char* r_name, Direction direction=None); // new room is the new currRoom, if there are no rooms by that name - return nullptr;
	void printCurrMap();
	Map* changeCurrMap(char* m_name); // if there are no maps by that name - return nullptr
	// Esty:
	bool addItemToRoom(char* i_name);
	bool addMonsterToRoom(char* m_name);
	bool addItemToDataRoom(char* r_name, char* i_name);
	bool addMonsterToDataRoom(char* r_name, char* m_name);
	void printData(); // prints only maps and rooms names.

	// Almog:
	Map* CombineCurrMapToMap(char* m_name); // (operator+=)
	Map* CombineMapsToNew(char* new_m_name, char* m_name); // (operator+)

private:
	Map* currentMap;
	Data* data;
};


