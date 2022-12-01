#include <iostream>
#include "ClapTrap.hpp"

int main(void) {
	ClapTrap a;
	ClapTrap b("No.1");
    ClapTrap c(b);
	ClapTrap d("No.2");

	a.attack("No.2");
	d.takeDamage(0);
	c.attack("No.2");
	d.takeDamage(0);
	c.beRepaired(100);
}
