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
	Item();
	~Item();

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