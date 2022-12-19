
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

Room::Room(const char* name)
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

// do not copy exits (connections)
Room& Room::operator=(const Room& other)
{
	if (this == &other) return *this;

	if (!(num_of_items == other.num_of_items))
	{
		delete[] items;
		items = new Item[other.num_of_items];
		if (items == nullptr) throw "no memory!";
	}
	memcpy_s(items, sizeof(Item)*other.num_of_items, other.items, sizeof(Item) * other.num_of_items);

	if (!(num_of_monsters == other.num_of_monsters))
	{
		delete[] monsters;
		monsters = new Monster[other.num_of_monsters];
		if (monsters == nullptr) throw "no memory!";
	}
	memcpy_s(monsters, sizeof(Monster) * other.num_of_monsters, other.monsters, sizeof(Monster) * other.num_of_monsters);

	delete[] name;
	char* temp_name = new char[strlen(other.name) + 1];
	if (!temp_name) throw "no memory!";
	strcpy_s(temp_name, sizeof(char) * strlen(other.name), other.name);
	name = temp_name;

	return *this;
}

char* Room::getName() const
{
	char* temp = new char[strlen(name) + 1];
	if (!temp) return nullptr;

	strcpy_s(temp, (sizeof(char)) * (strlen(name) + 1), name);
	temp[strlen(name)] = 0;
	return temp;
}

int Room::getNumOfItems() const
{
	return num_of_items;
}

int Room::getNumOfMonsters() const
{
	return num_of_monsters;
}

Room* Room::getNextRoom(Direction direction) const
{
	if (direction == North) return north;
	if (direction == East) return east;
	if (direction == South) return south;
	if (direction == West) return west;
	if (direction == None) return nullptr;
	return nullptr;
}

Direction Room::canRoomConnect() const
{
	if (north) return North;
	if (east) return East;
	if (south) return South;
	if (west) return West;
	return None;
}

void Room::printRoom()
{
	std::cout << "Room " << name << ": " << std::endl;
	std::cout << "Items:" << std::endl;
	for (size_t i = 0; i < num_of_items; i++)
	{
		std::cout << (i + 1) << ". ";
		items[i].print();
		std::cout << std::endl;
	}
	std::cout << "Monsters:" << std::endl;
	for (size_t i = 0; i < num_of_monsters; i++)
	{
		std::cout << (i + 1) << ". ";
		monsters[i].print();
		std::cout << std::endl;
	}
}

bool Room::addItem(char* name)
{

	if (!name) {
		return false;
	}

	for (int i = 0; i < num_of_items; i++)
	{
		//Item is already exists
		if (strcmp(name, items[i].getName()) == 0 && items[i].getRarity() != Legendary)
		{
			items[i]++;
			return true;
		} // same item level not legendary
	}
	//Add new Item
	Item* newArr = new Item[++num_of_items];
	if (!newArr) return false;

	newArr[num_of_items - 1] = Item(name);

	if (!&newArr[num_of_items - 1])
	{
		delete[] newArr;
		return false;
	}

	memcpy_s(newArr, sizeof(Item) * (num_of_items - 1), items, sizeof(Item) * (num_of_items - 1));

	delete[] items;
	items = newArr;
	return true;
}


bool Room::addMonster(char* name)
{
	for (int i = 0; i < num_of_monsters; i++)
	{
		if (strcmp(name, monsters[i].getName()) == 0 && monsters[i].getLevel() < 5)
		{
			monsters[i]++;
			return true;
		}
	}

	Monster* newArr = new Monster[++num_of_monsters];
	if (!newArr) return false;

	newArr[num_of_monsters - 1] = Monster(name);

	if (!&newArr[num_of_monsters - 1])
	{
		delete[] newArr;
		return false;
	}

	memcpy_s(newArr, sizeof(Monster) * (num_of_monsters - 1), items, sizeof(Monster) * (num_of_monsters - 1));

	delete[] monsters;
	monsters = newArr;
	return true;
}

// connects rooms in both ways
bool Room::connectRoom(Room* room, Direction direction)
{
	if (direction == None) return false;
	if (!room) return false;
	if (!this->getNextRoom(direction)) return false;
	if (room->canRoomConnect() == None) return false;

	if (direction == North) this->north = room;
	if (direction == East) this->east = room;
	if (direction == South) this->south = room;
	if (direction == West) this->west = room;

	if (room->canRoomConnect() == North) room->north = this;
	if (room->canRoomConnect() == East) room->east = this;
	if (room->canRoomConnect() == South) room->south = this;
	if (room->canRoomConnect() == West) room->west = this;

	return true;
}
