#include "map.h"
#include <string.h>
#include <iostream>

using namespace std;

Map::Map()
{
	name = nullptr;
	rooms = nullptr;
	rooms_array = nullptr;
	currentRoom = nullptr;

}

 Map::Map(const Map& m)
{
	 num_of_rooms = m.num_of_rooms;
	 name = new char[strlen(m.name) + 1];
	 if (!name) throw "No memory!";

	 currentRoom = m.currentRoom;

	 for (int i = 0; i < num_of_rooms; i++)
	 {
		 rooms_array[i] = m.rooms_array[i];
	 }

	 for (int i = 0; i < num_of_rooms; i++)
	 {
		 rooms[i] = m.rooms[i];
	 }

	 
	 for (int i = 0; i < num_of_rooms; i++)
	 {
		 char* h_name = new char(sizeof(m.rooms[i].getNextRoom(North)->getName()) + 1);
		 if (!h_name) throw "No memory!";
		 strcpy(h_name, m.rooms[i].getNextRoom(North)->getName());

		 for (int j = 0; j < num_of_rooms; j++)
		 {
			 if (rooms[j].getName() == h_name)
			 {
				 rooms[i].connectRoom(rooms[j].getNextRoom(North), North);
			 }
		 }
		 delete[] h_name;
		
		 char* h_name = new char(sizeof(m.rooms[i].getNextRoom(South)->getName()) + 1);
		 if (!h_name) throw "No memory!";
		 strcpy(h_name, m.rooms[i].getNextRoom(South)->getName());

		 for (int j = 0; j < num_of_rooms; j++)
		 {
			 if (rooms[j].getName() == h_name)
			 {
				 rooms[i].connectRoom(rooms[j].getNextRoom(South), South);
			 }
		 }
		 delete[] h_name;

		 char* h_name = new char(sizeof(m.rooms[i].getNextRoom(East)->getName()) + 1);
		 if (!h_name) throw "No memory!";
		 strcpy(h_name, m.rooms[i].getNextRoom(East)->getName());

		 for (int j = 0; j < num_of_rooms; j++)
		 {
			 if (rooms[j].getName() == h_name)
			 {
				 rooms[i].connectRoom(rooms[j].getNextRoom(East), East);
			 }
		 }
		 delete[] h_name;
			
		 char* h_name = new char(sizeof(m.rooms[i].getNextRoom(West)->getName()) + 1);
		 if (!h_name) throw "No memory!";
		 strcpy(h_name, m.rooms[i].getNextRoom(West)->getName());

		 for (int j = 0; j < num_of_rooms; j++)
		 {
			 if (rooms[j].getName() == h_name)
			 {
				 rooms[i].connectRoom(rooms[j].getNextRoom(West), West);
			 }
		 }
		 delete[] h_name;
			
		
	 }
}

Map::Map(const char* n)
{
	//Name of map
	char* temp_name = new char[strlen(n)+1];
	if (!temp_name) throw "no memory!";
	strncpy(temp_name, n, strlen(n));
	name = temp_name;

	num_of_rooms = 1;

	
	Room* new_room = new Room(temp_name);
	if (!new_room)  throw  "No memory";
	//Rooms 
	rooms = new_room;

	//Rooms array
	
	*rooms_array[num_of_rooms-1] = new_room;

	//Current room
	currentRoom = rooms;
}

Map::~Map()
{
	delete[] rooms;
	delete[] currentRoom;
	delete[] name;
	delete[] rooms_array;
}


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

int Map::getNumOfRooms() const
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
	return currentRoom->addItem(name);
	
}
bool Map::addMosterToCurrRoom(char* name)
{
	return currentRoom->addMonster(name);
}

Direction Map::whatIsEmpty()
{
	return currentRoom->canRoomConnect();
		
}
