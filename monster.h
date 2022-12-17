#pragma once

class Monster
{
public:

	// Esty:
	Monster::Monster();
	Monster(char* n);
	~Monster();

	int getLevel();
	char* getName();
	int operator++();


	// operator++

private:
	char* name;
	int level;
};

Monster::Monster(){}

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
