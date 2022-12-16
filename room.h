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

	// Almog:
	Room();
	Room(Room*);
	Room(char* name);
	~Room();

	Room& operator=(const Room& other);

	// Almog:
	char* getName();
	int getNumOfItems();
	int getNumOfMonsters();
	Room* getNextRoom(Direction direction);
	Direction canRoomConnect();

	void printRoom();

	// Esty:
	bool addItem(char* name);
	bool addMonster(char* name);

	bool connectRoom(Room* room, Direction direction);
	
	

private:
	const char* name;
	Item* items;
	Monster* monsters;
	Room* north;
	Room* east;
	Room* south;
	Room* west;

	int num_of_items;
	int num_of_monsters;
};


