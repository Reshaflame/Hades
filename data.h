#pragma once

#include "map.h"
#include "room.h"

class Data
{
public:

	// Almog
	Data();
	~Data();

	// Almog:
	Room* addRoom(char* name);
	Map* addMap(char* name);
	
	// Esty:
	bool addItem(char* r_name, char* i_name);
	bool addMonster(char* r_name, char* m_name);

	// Esty:
	Map* getMap(char* m_name);

	// Almog:
	Room* getRoom(char* r_name);

	// Esty:
	void printData(); 
private:
	int num_of_rooms;
	int num_of_maps =;

	Map* maps;
	Room* rooms;
};
