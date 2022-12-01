#include "Zombie.hpp"

int main(void)
{
	Zombie *horde = zombieHorde(10, "One of them");

	horde[0].announce();
	horde[11].announce();
	horde->announce();
	delete[] horde;
	horde = nullptr;
}