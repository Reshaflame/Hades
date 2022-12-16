#pragma once

class Monster
{
public:

	// Esty:
	Monster();
	~Monster();

	int getLevel();
	char* getName();


	// operator++

private:
	const char* name;
	int level = 1;
};

Monster::Monster()
{
}

Monster::~Monster()
{
}