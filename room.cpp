
#include "room.h"
#include <iostream>

Room::Room()
{
	name = nullptr;
	items = nullptr;
	monsters = nullptr;
	north = nullptr;
	east = nullptr;
	south = nullptr;
	west = nullptr;
	num_of_items = 0;
	num_of_monsters = 0;
}

Room::~Room()
{
	delete name;
	delete[] items;
	delete[] monsters;
}

Room::Room(Room* room)
{
	if (!room) throw "Null argument!!";

	char* temp_n = new char[strlen(room->name) + 1];
	if (!temp_n) throw "no memory!";

	strcpy_s(temp_n, (sizeof(char) * (strlen(room->name) + 1)), room->name);
	temp_n[strlen(room->name)] = 0;
	name = temp_n;

	items = new Item[room->num_of_items];
	if (!items) throw "no memory!";

	memcpy_s(items, sizeof(Item) * room->num_of_items, room->items, sizeof(Item) * room->num_of_items);

	monsters = new Monster[room->num_of_monsters];
	if (!monsters) throw "no memory!";

	memcpy_s(monsters, sizeof(Monster) * room->num_of_monsters, room->monsters, sizeof(Monster) * room->num_of_monsters);

	north = nullptr;
	east = nullptr;
	south = nullptr;
	west = nullptr;

	num_of_items = room->num_of_items;
	num_of_monsters = room->num_of_monsters;
	
}

Room::Room(char* name)
{
	if (!name) throw "Null argument!!";

	char* temp_n = new char[strlen(name) + 1];
	if (!temp_n) throw "no memory!";

	strcpy_s(temp_n, (sizeof(char) * (strlen(name) + 1)), name);
	temp_n[strlen(name)] = 0;
	this->name = temp_n;

	items = nullptr;
	monsters = nullptr;

	north = nullptr;
	east = nullptr;
	south = nullptr;
	west = nullptr;

	num_of_items = 0;
	num_of_monsters = 0;
}
