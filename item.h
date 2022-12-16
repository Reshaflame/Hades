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
	~Item();

	Rarity getRarity();
	char* getName();

	// operator++

private:
	Rarity(common);
	const char* name;
};

Item::Item()
{
}

Item::~Item()
{
}