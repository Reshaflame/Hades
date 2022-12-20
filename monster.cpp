
#include "monster.h"
#include <iostream>

using namespace std;

void Monster::print()
{
	std::cout << name << " Level: " << level;
}

int Monster::getLevel() const
{
	return level;
}

const char* Monster::getName() const
{
	if (!name) return nullptr;

	char* temp = new char[strlen(name) + 1];
	if (!temp) throw "no memory!";

	strcpy_s(temp, sizeof(char) * strlen(name), name);
	temp[strlen(name) + 1] = 0;
	return temp;

}

Monster& Monster::operator++()
{
	if (level < 5) ++level;
	return *this;
}

Monster Monster::operator++(int)
{
	Monster old = *this;
	operator++();
	return old;
}

Monster::Monster() 
{
	name = nullptr;
	level = 1;
}

Monster::Monster(char* n)
{
	char* temp = new char[strlen(n) + 1];
	if (!temp) throw "no memory!";

	strcpy_s(temp, sizeof(char)*strlen(n), n);
	temp[strlen(n) + 1] = 0;
	name = temp;
	level = 1;

}

Monster::~Monster()
{
	delete[] name;
}