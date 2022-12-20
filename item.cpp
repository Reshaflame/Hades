
#include "item.h"
#include <iostream>

using namespace std;

Item::Item()
{
	name = nullptr;
	rarity = Common;
}

Item::Item(char* name)
{
	if (!name) throw "Null argument!!";

	char* temp_n = new char[strlen(name) + 1];
	if (!temp_n) throw "no memory!";

	strcpy_s(temp_n, (sizeof(char) * (strlen(name) + 1)), name);
	temp_n[strlen(name)] = 0;
	this->name = temp_n;
	rarity = Common;
}

Item::~Item()
{
	delete[] name;
}

Item::Item(const Item& item)
{
	rarity = item.rarity;
	char* temp_n = new char[strlen(item.name) + 1];
	if (!temp_n) throw "no memory!";

	strcpy_s(temp_n, (sizeof(char) * (strlen(item.name) + 1)), name);
	temp_n[strlen(item.name)- 1] = 0;
	this->name = temp_n;
}

Rarity Item::getRarity() const
{
	return rarity;
}

const char* Item::getName() const
{ 
	return name;
}

Item& Item::operator++() {
	if (rarity == Common) rarity = Uncommon;
	if (rarity == Uncommon) rarity = Epic;
	if (rarity == Epic) rarity = Legendary;
	if (rarity == Legendary) rarity = Legendary;
	return *this;
}

Item Item::operator++(int)
{
	Item old = *this;
	operator++();
	return old;
}

void Item::print()
{
	std::cout << name << " Rarity: ";
	if (rarity == Common) std::cout << "common";
	else if (rarity == Uncommon) std::cout << "uncommon";
	else if (rarity == Epic) std::cout << "epic";
	else if (rarity == Legendary) std::cout << "legendary";
}