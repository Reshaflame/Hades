#pragma once

#include "room.h";

class Map
{
public:
	Map();
	~Map();

	
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

	int num_of_rooms = 0;
};

Map::Map()
{
}

Map::~Map()
{
}