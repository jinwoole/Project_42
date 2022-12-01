#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>

class ClapTrap {
	protected:
		std::string name;
		unsigned int hit_point;
		unsigned int energy_point;
		unsigned int attack_damage;
	public:
		ClapTrap();
		ClapTrap(std::string _name);
		ClapTrap(const ClapTrap& other);
		ClapTrap& operator=(const ClapTrap& other);
		~ClapTrap();
		void attack(const std::string& traget);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};

#endif