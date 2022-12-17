
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

bool Room::addItem(char* name)
{
	
	for (int i = 0; i < num_of_items; i++) 
	{
		//Item is already exists
		if (strcmp(name, items[i].getName()) == 0)
		{
			if (items[i].getRarity() == Legendary) //His level is legendary
			{
				for (int j = i; j < num_of_items; j++) // search for more
				{
					if (strcmp(name, items[j].getName()) == 0 && items[j].getRarity() != Legendary) // same item level not legendary
					{
						items[i].operator++();
					}
					
				}
			}
			else {
				items[i].operator++();
			}
		}

	}
	//Add new Item
	
	Item* newArr = new Item[++num_of_items];
	if (!newArr) return false;
	
	memcpy_s(newArr, sizeof(Item) * (num_of_items - 1), items, sizeof(Item) * (num_of_items - 1));

	newArr[num_of_items - 1] = Item(name);
	if (!&newArr[num_of_items - 1])
	{
		delete[] newArr;
		return false;
	}

	delete[] items;
	items = newArr;
	return true;
		
		
}
bool Room::addMonster(char* name)
{
	for (int i = 0; i < num_of_monsters; i++)
	{
		if (strcmp(name, monsters[i].getName()) == 0)
		{
			if (monsters[i].getLevel() == 5)
			{
				for (int j = i; j < num_of_monsters; j++) // search for more
				{
					if (strcmp(name, monsters[j].getName()) == 0 && monsters[j].getLevel() != 5) // same monster level not 5
					{
					monsters[i].operator++();
					}
					
				}
					
			}

		}
		else {
			monsters[i].operator++();
		}
	}
	
	Monster* newArr = new Monster[++num_of_monsters];
	if (!newArr) return false;

	memcpy_s(newArr, sizeof(Monster) * (num_of_monsters - 1), monsters, sizeof(Monster) * (num_of_monsters - 1));

	newArr[num_of_monsters - 1] = Monster(name);
	if (!&newArr[num_of_monsters - 1])
	{
		delete[] newArr;
		return false;
	}

	delete[] monsters;
	monsters = newArr;
	return true;
	
}
bool Room::connectRoom(Room* room, Direction direction)
{

	switch (this->canRoomConnect())
	{
	case North:
	{
		switch (room->canRoomConnect())
		{
		case North:
			this->north = room;
			room->north = this;
			return true;
			break;
		case South:
			this->north = room;
			room->south = this;
			return true;
			break;
		case East:
			this->north = room;
			room->east = this;
			return true;
			break;
		case West:
			this->north = room;
			room->west = this;
			return true;
			break;
		case None:
			return false;
			break;

		default:
			return false;
			break;
		}
	}
		break;
	case South:
	{
		switch (this->canRoomConnect())
		{
		case North:
			this->south = room;
			room->north = this;
			return true;
			break;
		case South:
			this->south = room;
			room->south = this;
			return true;
			break;
		case East:
			this->south = room;
			room->east = this;
			return true;
			break;
		case West:
			this->south = room;
			room->west = this;
			return true;
			break;
		case None:
			return false;
			break;
		default:
			return false;
		break;
		}
	}
		break;

	case East:
	{
		switch (this->canRoomConnect())
		{
		case North:
			this->east = room;
			room->north = this;
			return true;
			break;
		case South:
			this->east = room;
			room->south = this;
			return true;
			break;
		case East:
			this->east = room;
			room->east = this;
			return true;
			break;
		case West:
			this->east = room;
			room->west = this;
			return true;
			break;
		case None:
			return false;
			break;

		default:
			return false;
			break;
		}
	}
		break;

	case West:
	{
		switch (this->canRoomConnect())
		{
		case North:
			this->west = room;
			room->north = this;
			return true;
			break;
		case South:
			this->west = room;
			room->south = this;
			return true;
			break;
		case East:
			this->west = room;
			room->east = this;
			return true;
			break;
		case West:
			this->west = room;
			room->west = this;
			return true;
			break;
		case None:
			return false;
			break;

		default:
			return false;
			break;
		}
	}
		break;

	case None:
		return false;
		break;

	default:
		return false;
		break;
	}
	
}
