#include "Zombie.hpp"
#include <iostream>


Zombie::Zombie(std::string name) //생성자
{
	Zombie::name = name;
}

void Zombie::announce()
{
	std::cout << name << ": BraiiiiiiinnnzzzZ" << std::endl;
}

Zombie::~Zombie() //소멸자
{
	std::cout << Zombie::name << " is killed brutelly by a destructor!!" << std::endl;
}