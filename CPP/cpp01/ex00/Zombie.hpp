#ifndef ZOMBIE_CPP
# define ZOMBIE_CPP

#include <string>

class Zombie {
	private:
		std::string name;
	public:
		Zombie(std::string name); //생성자
		void announce();
		~Zombie(); //소멸자
};

void	randomChump(std::string name);
Zombie*	newZombie(std::string name);

#endif