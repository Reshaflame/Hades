#pragma once

enum  Rarity
{
	Common = 1,
	Uncommon,
	Epic,
	Legendary
};

class Item
{
public:

	// Esty:
	Item::Item();
	Item(char* n);
	Item(const Item& i)
	{
		rare = i.rare;
		name  = new char[strlen(i.name) + 1];
		if (name == nullptr)
			delete[] name;
		strncpy(name, i.name, strlen(i.name) + 1);
	}
	~Item();

	Rarity getRarity();
	char* getName();
	Rarity& operator++();
	

	// operator++

private:
	Rarity rare;
	char* name;
	Item() : name(nullptr),rare(Common){}
};
Item::Item(){}

Item::Item(char* n)
{
	name = new char[strlen(n) + 1];
	if (name == nullptr)
		delete[] name;
	strncpy(name, n, strlen(n) + 1);
	rare = Common;
}

Item::~Item()
{
	delete[] name;
}
