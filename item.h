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
	~Item();

	Rarity getRarity()const;
	char* getName()const;
	Item operator++();
	void print();


private:
	Rarity rarity;
	char* name;
};



