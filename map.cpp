
#include "map.h"
#include <iostream>

Map::Map(const char* n)
{
	//Name of map
	char* temp_name = new char[strlen(n) + 1];
	if (!temp_name) throw "no memory!";
	strncpy(temp_name, n, strlen(n));
	name = temp_name;

	num_of_rooms = 0;

	rooms = nullptr;

	rooms_array = nullptr;

	currentRoom = nullptr;

}

Map::Map(const Map& m)
{
	num_of_rooms = m.num_of_rooms;

	char* temp = new char[strlen(m.name) + 1];
	if (!temp) throw "No memory!";

	strcpy_s(temp, (sizeof(char) * (strlen(m.name))), m.name);
	temp[strlen(m.name)-1] = 0;
	name = temp;

	// checks if map isn't empty
	if (num_of_rooms)
	{
		// copies the rooms without connections
		for (int i = 0; i < num_of_rooms; i++)
		{
			*rooms_array[i] = *m.rooms_array[i];
		}

		// copies the connections
		for (int i = 0; i < num_of_rooms; i++)
		{
			char* roomName = m.rooms_array[i]->getNextRoom(North)->getName();
			Room* to_connect = nullptr;

			if (roomName)
			{
				for (size_t j = 0; j < num_of_rooms && !to_connect; j++)
				{
					if (!strcmp(rooms_array[j]->getName(), roomName))
						to_connect = rooms_array[j];
				}
				rooms_array[i]->connectRoom(to_connect, North);

			}

			roomName = m.rooms_array[i]->getNextRoom(East)->getName();
			to_connect = nullptr;

			if (roomName)
			{
				for (size_t j = 0; j < num_of_rooms && !to_connect; j++)
				{
					if (!strcmp(rooms_array[j]->getName(), roomName))
						to_connect = rooms_array[j];
				}
				rooms_array[i]->connectRoom(to_connect, East);

			}

			roomName = m.rooms_array[i]->getNextRoom(South)->getName();
			to_connect = nullptr;

			if (roomName)
			{
				for (size_t j = 0; j < num_of_rooms && !to_connect; j++)
				{
					if (!strcmp(rooms_array[j]->getName(), roomName))
						to_connect = rooms_array[j];
				}
				rooms_array[i]->connectRoom(to_connect, South);

			}

			roomName = m.rooms_array[i]->getNextRoom(West)->getName();
			to_connect = nullptr;

			if (roomName)
			{
				for (size_t j = 0; j < num_of_rooms && !to_connect; j++)
				{
					if (!strcmp(rooms_array[j]->getName(), roomName))
						to_connect = rooms_array[j];
				}
				rooms_array[i]->connectRoom(to_connect, West);

			}
		}

		// copy the current room from m
		currentRoom = nullptr;
		for (size_t i = 0; i < num_of_rooms && !currentRoom; i++)
		{
			if (!strcmp(m.currentRoom->getName(), rooms_array[i]->getName())) currentRoom = rooms_array[i];
		}

		rooms = rooms_array[0];
	}
	else
	{
		rooms = nullptr;

		rooms_array = nullptr;

		currentRoom = nullptr;
	}
	
}

Map::~Map()
{
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

	if(!currentRoom->connectRoom(room, direction)) return nullptr;

	return currentRoom->getNextRoom(direction);
}

// combine two maps - if there are room duplicity ther return "left" map unchanged
bool Map::combineMaps(Map& l_map, const Map& r_map)
{
	// if right map is empty
	if (r_map.num_of_rooms == 0) return true;

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

	// if left map isn't empty - search connection
	if (l_map.num_of_rooms)
	{
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

	}
	
	// all is fine and expanding left map to fit the right one
	size_t old_size = l_map.num_of_rooms;
	if (!l_map.expandRoomsArr(old_size + r_map.num_of_rooms)) return false;
	l_map.num_of_rooms = old_size + r_map.num_of_rooms;

	// copies the rooms from right map to left map
	for (size_t i = old_size; i < l_map.num_of_rooms; i++)
	{
		*l_map.rooms_array[i] = *r_map.rooms_array[i - old_size]; // copies without connections
	}

	// copies the connections
	for (size_t i = old_size; i < l_map.num_of_rooms; i++)
	{
		char* roomName = r_map.rooms_array[i - old_size]->getNextRoom(North)->getName();
		Room* roomToConnect = nullptr;
		if (roomName)
		{
			for (size_t j = old_size; j < l_map.num_of_rooms && !roomToConnect; j++)
			{
				if (!strcmp(l_map.rooms_array[j]->getName(), roomName))
					roomToConnect = l_map.rooms_array[j];
			}
			l_map.rooms_array[i]->connectRoom(roomToConnect, North);
		}

		roomName = r_map.rooms_array[i - old_size]->getNextRoom(East)->getName();
		if (roomName)
		{
			for (size_t j = old_size; j < l_map.num_of_rooms && !roomToConnect; j++)
			{
				if (!strcmp(l_map.rooms_array[j]->getName(), roomName))
					roomToConnect = l_map.rooms_array[j];
			}
			l_map.rooms_array[i]->connectRoom(roomToConnect, East);
		}
		
		roomName = r_map.rooms_array[i - old_size]->getNextRoom(South)->getName();
		if (roomName)
		{
			for (size_t j = old_size; j < l_map.num_of_rooms && !roomToConnect; j++)
			{
				if (!strcmp(l_map.rooms_array[j]->getName(), roomName))
					roomToConnect = l_map.rooms_array[j];
			}
			l_map.rooms_array[i]->connectRoom(roomToConnect, South);
		}

		roomName = r_map.rooms_array[i - old_size]->getNextRoom(West)->getName();
		if (roomName)
		{
			for (size_t j = old_size; j < l_map.num_of_rooms && !roomToConnect; j++)
			{
				if (!strcmp(l_map.rooms_array[j]->getName(), roomName))
					roomToConnect = l_map.rooms_array[j];
			}
			l_map.rooms_array[i]->connectRoom(roomToConnect, West);
		}
	}

	// if left map wasn't empty
	if (connection1 != None)
	{
		// connects the two maps together 
		l_map.rooms_array[room_1_i]->connectRoom(l_map.rooms_array[room_2_i], connection1);
		l_map.rooms_array[room_2_i]->connectRoom(l_map.rooms_array[room_1_i], connection2);
	}
	// if left map was empty - starting room is the first room in the array
	else
	{
		l_map.rooms = l_map.rooms_array[0];
	}
	// left map's current room is the last room that was added to the array of the right map.
	l_map.currentRoom = l_map.rooms_array[l_map.num_of_rooms - 1];
	return true;
}

bool Map::expandRoomsArr(int new_size)
{
	if (new_size <= num_of_rooms) return false;

	Room** new_arr = new Room * [new_size];
	if (!new_arr) return false;

	memcpy_s(new_arr, sizeof(Room*) * num_of_rooms, rooms_array, sizeof(Room*) * num_of_rooms);

	for (size_t i = num_of_rooms; i < new_size; i++)
	{
		new_arr[i] = nullptr;
	}
	delete[] rooms_array;
	rooms_array = new_arr;
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

Map& Map::operator+=(const Map& map_to_add)
{
	if (!combineMaps(*this, map_to_add))
	{
		std::cout << "not able to copy!";
	}
	return *this;
}
