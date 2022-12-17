#pragma once

#include "room.h";

class Map
{
public:

	// Esty:
	Map();
	Map(char*);
	Map(const Map&);
	~Map();

	// Almog
	void printMap();

	char* getName();
	int getNumOfRooms();
	Room* getCurrRoom();

	Room* addRoom(Room* room, Direction direction);
	
	// Esty:
	bool addItemToCurrRoom(char* name);
	bool addMosterToCurrRoom(char* name);

	Direction whatIsEmpty();

	// HARD!
	Map& operator+=(const Map& map_to_add);
	friend Map operator+(Map l_map, const Map& r_map)
	{
		l_map += r_map;
		return l_map;
	}
	

private:
	const char* name;
	Room* rooms;
	Room** romms_array;
	Room* currentRoom;

	int num_of_rooms = 0;
	
	// Almog:
	bool combineMaps(Map l_map, const Map& r_map);
	bool expandRoomsArr(int new_size);
};
Map::Map(char* n)
{
	name = new char[strlen(n) + 1];
	if (name == nullptr)
		delete[] name;
	strncpy(name, n, strlen(n) + 1);

	
}

Map::~Map()
{
	delete[] rooms;
	delete[] currentRoom;
	delete[] name;
}

