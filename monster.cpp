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
