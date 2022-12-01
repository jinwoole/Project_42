#include "WrongCat.hpp"
#include <iostream>

int main() 
{
	WrongAnimal* meta = new WrongAnimal(); 
	WrongAnimal* i = new WrongCat();


	std::cout << i->getType() << " " << std::endl; 
	i->makeSound(); //will output the cat sound! j->makeSound();
	meta->makeSound();

	std::cout << "--time to kill--" << std::endl;
	delete meta;
	WrongCat* j = (WrongCat*)i;
	delete j;
	std::cout << "--all is done--" << std::endl;

	delete meta;
	delete i;
	return 0;
}