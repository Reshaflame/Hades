#pragma once

#include "room.h";

class Map
{
public:

	// Esty:
	Map();
	Map(char* n, char* r);
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
	Room** rooms_array;
	Room* currentRoom;

	int num_of_rooms;
	
	// Almog:
	bool combineMaps(Map l_map, const Map& r_map);
	bool expandRoomsArr(int new_size);
};
Map::Map(const char* n, char* r)
{
	//Name of map
	char* temp_name = new char[strlen(n)+1];
	if (!temp_name) throw "no memory!";
	strncpy(temp_name, n, strlen(n));
	name = temp_name;

	num_of_rooms = 1;

	
	Room* new_room = new Room(r);
	if (!new_room)  throw  "No memory";
	//Rooms 
	rooms = new_room;

	//Rooms array
	
	*rooms_array[num_of_rooms-1] = new_room;

	//Current room
	currentRoom = rooms;
	
	
}
Map::~Map()
{
	delete[] rooms;
	delete[] currentRoom;
	delete[] name;
	delete[] rooms_array;
}

