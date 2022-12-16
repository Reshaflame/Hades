#pragma once

#include "item.h"
#include "monster.h"

enum Direction
{
	North = 12,
	East = 3,
	South = 6,
	West = 9,
	None = 0
};

class Room
{
public:
	Room();
	~Room();

private:
	const char* name;
	Item* items;
	Monster* monsters;
	Room* north = nullptr;
	Room* east = nullptr;
	Room* south = nullptr;
	Room* west = nullptr;

	int num_of_items = 0;
	int num_of_monsters = 0;
};

Room::Room()
{
}

Room::~Room()
{
}

