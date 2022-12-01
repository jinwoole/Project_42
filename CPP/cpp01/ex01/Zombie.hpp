#ifndef ZOMBIE_CPP
# define ZOMBIE_CPP

#include <string>

class Zombie {
	private:
		std::string name;
	public:
		Zombie();
		void nameZombie(std::string name);
		void announce();
		~Zombie(); //소멸자
};

Zombie* zombieHorde(int N, std::string name);

#endif