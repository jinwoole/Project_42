#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name)
{
	Zombie* ret = new Zombie[N];
	int i = 0;

	while (i < N)
	{
		ret[i].nameZombie(name);
		i++;
	}
	return ret;
}
