#pragma once

class Monster
{
public:

	// Esty:
	Monster();
	Monster(char* n);
	~Monster();

	int getLevel() const;
	const char* getName() const;
	
	Monster& operator++();
	Monster operator++(int);

	// Almog:

	void print();

private:
	const char* name;
	int level;
};

