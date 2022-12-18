#include "item.h"
#include <string.h>

using namespace std;


Rarity Item::getRarity()
{
	return rare;
}
char* Item::getName()
{
	return name;
}

Rarity& Item::operator++() {
	if (rare == Common) return rare = Uncommon;
	if (rare == Uncommon) return rare = Epic;
	if (rare == Epic) return rare = Legendary;
	if (rare == Legendary) return rare = Legendary;
	
}

void Item::print()
{
	std::cout << name << " Rarity: ";
	if (rarity == Common) std::cout << "common";
	else if (rarity == Uncommon) std::cout << "uncommon";
	else if (rarity == Epic) std::cout << "epic";
	else if (rarity == Legendary) std::cout << "legendary";
}
