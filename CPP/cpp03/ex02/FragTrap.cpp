#include "FragTrap.hpp"
#include <iostream>

FragTrap::FragTrap()
{
	name = "Unknown";
	hit_point = 100;
	energy_point = 100;
	attack_damage = 30;
	std::cout << ">> FragTrap " << name << " is constructed from ClapTrap. It's much better than privious one" << std::endl;
}

FragTrap::FragTrap(std::string _name)
{
	name = _name;
	hit_point = 100;
	energy_point = 100;
	attack_damage = 30;
	std::cout << ">> FragTrap " << name << " is constructed from ClapTrap. It's much better than privious one" << std::endl;
}

FragTrap::FragTrap(const FragTrap& other)
{
	name = other.name;
	hit_point = other.hit_point;
	energy_point = other.energy_point;
	attack_damage = other.attack_damage;
	std::cout << ">> FragTrap " << name << " is copied. It's not that useless I think" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other)
{
	name = other.name;
	hit_point = other.hit_point;
	energy_point = other.energy_point;
	attack_damage = other.attack_damage;
	std::cout << ">> FragTrap " << name << " is copied by an operator" << std::endl;

	return *this;
}

FragTrap::~FragTrap()
{
	std::cout << ">> FragTrap was so fragile actually" << std::endl;
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap : High Fives Guys!, but no one answered" << std::endl;
}