#pragma once

#include "map.h"
#include "room.h"

class Data
{
public:
	Data();
	~Data();

private:
	int num_of_rooms = 0;
	int num_of_maps = 0;

	Map* maps;
	Room* rooms;
};

Data::Data()
{
}

Data::~Data()
{
}