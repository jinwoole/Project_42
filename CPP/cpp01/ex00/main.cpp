#include "Zombie.hpp"

int main(void)
{
	Zombie zero = Zombie("stack one");
	Zombie *one = newZombie("heap one");

	one->announce();
	zero.announce();
	delete one;
	one = 0;
	randomChump("Chump");
}