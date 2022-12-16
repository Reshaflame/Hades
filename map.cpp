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
	
}
