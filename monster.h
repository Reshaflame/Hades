#pragma once

class Monster
{
public:
	Monster();
	~Monster();

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