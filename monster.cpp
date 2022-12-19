#include "monster.h"
#include <string.h>


using namespace std;

Monster::Monster(){
	name = nullptr;
	level = 0;
}

Monster::Monster(char* n)
{
	name = new char[strlen(n) + 1];
	if (name == nullptr)
		delete[] name;
	strncpy(name, n, strlen(n) + 1);
	level = 1;

}

Monster::~Monster()
{
	delete[] name;
}

int Monster::getLevel()const
{
	return level;
}
char* Monster::getName()const
{
	return name;
}

Monster& Monster::operator++()
{
	++level;
	if (level == 5) level = 5;
	return *this;
}

