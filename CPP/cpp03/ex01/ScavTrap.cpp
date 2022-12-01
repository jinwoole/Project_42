#include "ScavTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap()
{
	name = "Unknown";
	hit_point = 100;
	energy_point = 50;
	attack_damage = 20;
	std::cout << "- ScavTrap " << name << " is constructed from ClapTrap. It seems like better than previous one" << std::endl;
}

ScavTrap::ScavTrap(std::string _name)
{
	name = _name;
	hit_point = 100;
	energy_point = 50;
	attack_damage = 20;
	std::cout << "- ScavTrap " << name << " is constructed. It seems like better than previous one" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other)
{
	name = other.name;
	hit_point = other.hit_point;
	energy_point = other.energy_point;
	attack_damage = other.attack_damage;
	std::cout << "- ScavTrap " << name << " is copied. It's not that useless I think" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
	name = other.name;
	hit_point = other.hit_point;
	energy_point = other.energy_point;
	attack_damage = other.attack_damage;
	std::cout << "- ScavTrap " << name << " is copied by an operator" << std::endl;

	return *this;
}

ScavTrap::~ScavTrap()
{
	std::cout << "- ScavTrap is slowly stopped it's function" << std::endl;
}

void ScavTrap::guardGate()
{
	std::cout << "ScavTrap is not at the guard mode(actually nothing changed)" << std::endl;
}