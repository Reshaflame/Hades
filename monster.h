#pragma once

class Monster
{
public:

	// Esty:
	Monster();
	Monster(char* n);
	~Monster();

	int getLevel()const;
	char* getName()const;
	Monster& operator++();


	// operator++

private:
	char* name;
	int level;
};

