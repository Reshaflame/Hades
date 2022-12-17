#include "map.h"
#include <string.h>

using namespace std;

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
