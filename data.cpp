
#include "data.h"
#include <iostream>

Data::Data()
{
	num_of_maps = 0;
	num_of_rooms = 0;
	maps = nullptr;
	rooms = nullptr;
}

Data::~Data()
{
	delete[] maps;
	delete[] rooms;
}

Room* Data::addRoom(char* name)
{
	if (!name) return nullptr;

	for (size_t i = 0; i < num_of_rooms; i++)
	{
		if (!strcmp(name, rooms[i].getName())) return nullptr;
	}
	Room* newArr = new Room[++num_of_rooms];
	if (!newArr) return nullptr;
	
	memcpy_s(newArr, sizeof(Room) * (num_of_rooms - 1), rooms, sizeof(Room) * (num_of_rooms - 1));

	newArr[num_of_rooms - 1] = Room(name);
	if (!&newArr[num_of_rooms - 1])
	{
		delete[] newArr;
		return nullptr;
	}

	delete[] rooms;
	rooms = newArr;
	return &newArr[num_of_rooms - 1];
}

Map* Data::addMap(char* name)
{
	if (!name) return nullptr;

	for (size_t i = 0; i < num_of_maps; i++)
	{
		if (!strcmp(name, maps[i].getName())) return nullptr;
	}
	Map* newArr = new Map[++num_of_maps];
	if (!newArr) return nullptr;
	
	memcpy_s(newArr, sizeof(Map) * (num_of_maps - 1), maps, sizeof(Map) * (num_of_rooms - 1));

	newArr[num_of_maps - 1] = Map(name);
	if (!&newArr[num_of_maps - 1])
	{
		delete[] newArr;
		return nullptr;
	}

	delete[] maps;
	maps = newArr;
	return &newArr[num_of_maps - 1];
}

Room* Data::getRoom(char* r_name) const
{
	for (size_t i = 0; i < num_of_rooms; i++)
	{
		if (!strcmp(r_name, rooms[i].getName()))
		{
			return &rooms[i];
		}
	}
	return nullptr;
}
bool Data::addItem(char* r_name, char* i_name)
{
	bool isItemExis = false;
	for (int i = 0; i < num_of_rooms; i++)
	{
		if (strcmp(rooms[i].getName(), r_name) == 0) {
			isItemExis = true;
			break;
		}
	}

	if (isItemExis) {

		rooms->addItem(i_name);
		return true;
	}
}
bool Data::addMonster(char* r_name, char* m_name)
{
	bool isMonsterExist = false;
	for (int i = 0; i < num_of_rooms; i++)
	{
		if (strcmp(rooms[i].getName(), r_name) == 0) 
		{
			isMonsterExist = true;
			break;
		}
		
		
		
	}
	if (isMonsterExist)
	{
		rooms->addMonster(m_name);
		return true;
	}
	
}

Map* Data::getMap(char* m_name) const
{
	for (int i = 0; i < num_of_maps; i++)
	{
		if (strcmp(maps[i].getName(), m_name) == 0)
			return &maps[i];
	}
}

void Data::printData()
{
	for (int i = 0; i < num_of_maps; i++)
	{
		std::cout << maps[i].getName();
		
	}
	for (int i = 0; i < num_of_rooms; i++)
	{
		std::cout << rooms[i].getName();

	}
}

