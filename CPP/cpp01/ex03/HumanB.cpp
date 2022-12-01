#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(std::string name) : weapon(NULL), name(name)
{
}

void HumanB::attack()
{
	if (weapon == NULL)
	{
		std::cout << name << " don't have a weapon" << std::endl;
		return ;
	}
	std::cout << name << " attacks with their " << weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon weapon)
{
	this->weapon = &weapon;
}

HumanB::~HumanB()
{
}
