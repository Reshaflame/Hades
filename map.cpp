#include "map.h"
#include <iostream>

using namespace std;

void Map::printMap()
{
	std::cout << "Map " << name << ":" << std::endl;
	for (size_t i = 0; i < num_of_rooms; i++)
	{
		std::cout << (i+1) << ". ";
		rooms_array[i]->printRoom();
	}
}

char* Map::getName() const
{
	char* temp = new char[strlen(name) + 1];
	if (!temp) return nullptr;

	strcpy_s(temp, (sizeof(char))*(strlen(name)+1),name);
	temp[strlen(name)] = 0;
	return temp;
}

int Map::getNumOfRooms()
{
	return num_of_rooms;
}

Room* Map::getCurrRoom() const
{
	return currentRoom;
}

Room* Map::addRoom(Room* room, Direction direction)
{
	if (!room) return nullptr;

	if (currentRoom->getNextRoom(direction)) return nullptr;

	for (size_t i = 0; i < num_of_rooms; i++)
	{
		if (!strcmp(room->getName(), rooms_array[i]->getName()))
		{
			if (rooms_array[i]->canRoomConnect() != None)
			{
				currentRoom->connectRoom(room, direction);
				return currentRoom;
			}
			else
			{
				return nullptr;
			}
		}
	}

	Room** newRoomsArr = new Room * [++num_of_rooms];
	if (!newRoomsArr) return nullptr;

	if(num_of_rooms != 1)
	memcpy_s(newRoomsArr, sizeof(Room*) * (num_of_rooms - 1), rooms_array, sizeof(Room*) * (num_of_rooms - 1));

	newRoomsArr[num_of_rooms - 1] = room; // Warning not relevant
	delete[] rooms_array;
	rooms_array = newRoomsArr;

	currentRoom->connectRoom(room, direction);
	return currentRoom;
}




// combine two maps - if there are room duplicity ther return "left" map unchanged
bool Map::combineMaps(Map l_map, const Map& r_map)
{
	// checks for duplicates
	for (size_t i = 0; i < l_map.getNumOfRooms(); i++)
	{
		for (size_t j = 0; j < r_map.num_of_rooms; j++)
		{
			if (!strcmp(l_map.rooms_array[i]->getName(), r_map.rooms_array[j]->getName()))
			{
				return false;
			}
		}
	}

	Direction connection1 = None;
	char* room_1 = nullptr;
	size_t room_1_i = 0;
	Direction connection2 = None;
	char* room_2 = nullptr;
	size_t room_2_i = 0;

	// looks for a free connection in left map
	for (size_t i = 0; i < l_map.num_of_rooms && !room_1; i++)
	{
		connection1 = l_map.rooms_array[i]->canRoomConnect();
		if (connection1 != None)
		{
			room_1 = l_map.rooms_array[i]->getName();
			room_1_i = i;
		}
	}

	// looks for a free connection in right map
	for (size_t i = 0; i < r_map.num_of_rooms && !connection2; i++)
	{
		connection2 = r_map.rooms_array[i]->canRoomConnect();
		if (connection2 != None)
		{
			room_2 = r_map.rooms_array[i]->getName();
			room_2_i = i + l_map.num_of_rooms;
		}
	}

	// if one map is a loop - return false
	if (connection1 == None || connection2 == None) return false;

	// all is fine and expanding left map to fit the right one
	size_t old_size = l_map.num_of_rooms;
	if (!l_map.expandRoomsArr(old_size + r_map.num_of_rooms)) return false;
	l_map.num_of_rooms = old_size + r_map.num_of_rooms;

	// copies the rooms from right map to left map
	for (size_t i = old_size; i < l_map.num_of_rooms; i++)
	{
		*l_map.rooms_array[i] = *r_map.rooms_array[i - old_size]; // copies with connections
	}

	// connects the two maps together 
	l_map.rooms_array[room_1_i]->connectRoom(l_map.rooms_array[room_2_i], connection1);
	l_map.rooms_array[room_2_i]->connectRoom(l_map.rooms_array[room_1_i], connection2);

	return true;
}

bool Map::addItemToCurrRoom(char* name)
{
	currentRoom->addItem(name);
	return true;
}
bool Map::addMosterToCurrRoom(char* name)
{
	currentRoom->addMonster(name);
}

Direction Map::whatIsEmpty()
{
	if (currentRoom->canRoomConnect() == North)
		return North;
	if (currentRoom->canRoomConnect() == East)
		return East;
	if (currentRoom->canRoomConnect() == West)
		return West;
	if (currentRoom->canRoomConnect() == South)
		return South;
	if (currentRoom->canRoomConnect() == None)
		return None;
}
