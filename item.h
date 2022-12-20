#pragma once

enum Rarity
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
	Item();
	Item(char* n);
	Item(const Item& i);
	~Item();

	Rarity getRarity() const;
	const char* getName() const;

	Item& operator++();
	Item operator++(int);

	// Almog:
	void print();

private:
	Rarity rarity;
	const char* name;
};

