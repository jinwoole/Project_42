#include <iostream>
#include "ScavTrap.hpp"

int main(void) {
	ScavTrap a;
	ScavTrap b("No.1");
    ScavTrap c(b);
	ScavTrap d("No.2");

	a.attack("No.2");
	d.takeDamage(0);
	c.attack("No.2");
	d.takeDamage(0);
	c.beRepaired(100);
	d.guardGate();

	std::cout << a.hit_point << std::endl;
}
