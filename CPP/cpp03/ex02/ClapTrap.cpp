#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap()
{
	name = "Unknown";
	hit_point = 10;
	energy_point = 10;
	attack_damage = 0;
	std::cout << "ClapTrap " << name << " is constructed" << std::endl;
}

ClapTrap::ClapTrap(std::string _name)
{
	name = _name;
	hit_point = 10;
	energy_point = 10;
	attack_damage = 0;
	std::cout << "ClapTrap "<< name << " is constructed" << std::endl;
}


ClapTrap::ClapTrap(const ClapTrap& other)
{
    name = other.name;
	hit_point = other.hit_point;
	energy_point = other.energy_point;
	attack_damage = other.attack_damage;
	std::cout << "ClapTrap "<< name << " is copied. What a useless" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	name = other.name;
	hit_point = other.hit_point;
	energy_point = other.energy_point;
	attack_damage = other.attack_damage;
	std::cout << "ClapTrap "<< name << " is copied by a operator" << std::endl;

	return *this;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap is destructed brutally by a destructor. No Name for Dead Machine" << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
	if (hit_point == 0)
	{
		std::cout << "::" << name << "already knockdown" << std::endl;
		return ;
	}
	if (energy_point <= 0)
	{
		std::cout << "::" << name << " has no energy" << std::endl;
		return ;
	}
	energy_point--;
	std::cout << "::" << name << " causes " << attack_damage << " to the concept of " << target << ". so, it was useless" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (hit_point == 0)
    {
		std::cout << "::" << name << " already knockdown" << std::endl;
		return ;
	}
	if (hit_point <= amount)
	{
		std::cout << "::" << name << " knock down" << std::endl;
		hit_point = 0;
		return ;
	}
	hit_point -= amount;
	std::cout << "::" << name << " take " << amount << " of damage" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (energy_point <= 0)
	{
		std::cout << "::"<< name << " has no energy to repair" << std::endl;
		return ;
	}
	if (hit_point == 0)
	{
		std::cout << "You just activated my trap card. It revived" << std::endl;
		hit_point++;
	}
	hit_point += amount;
	std::cout << "::" << name << " repaired." << std::endl;
}