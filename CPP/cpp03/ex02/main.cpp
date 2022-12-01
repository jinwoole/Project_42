#include "FragTrap.hpp"

int main(void) {
	FragTrap a;
	FragTrap b("No.1");
    FragTrap c(b);
	FragTrap d("No.2");

	a.attack("No.2");
	d.takeDamage(0);
	c.attack("No.2");
	d.takeDamage(30);
	d.takeDamage(30);
	d.takeDamage(30);
	d.takeDamage(30);

	c.beRepaired(100);
	d.highFivesGuys();
}
