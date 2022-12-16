#include "monster.h"
#include <string.h>


using namespace std;


int Monster::getLevel() 
{
	return level;
}
char* Monster::getName()
{
	return name;
}

int Monster::operator++()
{
	++level;
	if (level == 5) return level = 5;
	return level;
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
	Item* new_item = new Item(name);
		if (new_item == nullptr)
			return false;
		++num_of_items;
		//create a new items array
		
		
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
	Monster* new_monster = new Monster(name);
	if (new_monster == nullptr)
		return false;
	++num_of_monsters;
	//create a new monsters array
	return true;
}

bool Room::connectRoom(Room* room, Direction direction)
{
	if (this->getName() == room->getName())
		return false;
	//add here more
	
}/*

	Direction canRoomConnect();
 */
