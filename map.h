#pragma once

#include "room.h";

class Map
{
public:

	// Esty:
	Map();
	Map(char* n);
	Map(const Map&);
	~Map();

	// Almog
	void printMap();

	char* getName() const;
	int getNumOfRooms() const;
	Room* getCurrRoom() const;

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



