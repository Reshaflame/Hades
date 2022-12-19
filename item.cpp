#include "item.h"
#include <iostream>
#include <string.h>

using namespace std;

Item::Item()
{
	rarity = Common;
	name = nullptr;
}

Item::Item(char* n)
{
	char* temp_name = new char[strlen(n) + 1];
	if (temp_name == nullptr){
		throw "NoMemory";
	}
	
	strncpy(temp_name, n, strlen(n) + 1);
	rarity = Common;
	name = temp_name;
}
Item::~Item()
{
	delete[] name;
}

Rarity Item::getRarity()const
{
	return rarity;
}
char* Item::getName()const
{
	return name;
}

Item Item::operator++() {
	if (rarity == Common) 
	{
		rarity = Uncommon;
	}
	if (rarity == Uncommon) 
	{
		 rarity = Epic;
	}
	if (rarity == Epic)
	{
		rarity = Legendary;
	} 
	if (rarity == Legendary) 
	{
		rarity = Legendary;
	}

	return *this;
}

void Item::print()
{
	std::cout << name << " Rarity: ";
	if (rarity == Common) std::cout << "common";
	else if (rarity == Uncommon) std::cout << "uncommon";
	else if (rarity == Epic) std::cout << "epic";
	else if (rarity == Legendary) std::cout << "legendary";
}
