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
	Room(const char* name);
	~Room();

	Room& operator=(const Room& other);

	

	// Almog:
	char* getName() const;
	int getNumOfItems() const;
	int getNumOfMonsters() const;
	Room* getNextRoom(Direction direction) const;
	Direction canRoomConnect() const;

	const char* getItemName(int index) const;
	const Rarity getItemRarity(int index) const;
	const char* getMonsterName(int index) const;
	const int getMonsterLevel(int index) const;

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

std::ostream& operator<<(std::ostream& os, const Room& room);

