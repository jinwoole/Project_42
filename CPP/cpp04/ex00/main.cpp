#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

int main(void)
{
	const Animal* meta = new Animal();
	const Animal* i = new Cat();
	const Animal* j = new Dog();

	std::cout << i->getType() << std::endl;
	std::cout << j->getType() << std::endl;

	i->makeSound();
	j->makeSound();
	meta->makeSound();

	std::cout << "====================================================" << std::endl;

	delete meta;
	delete i;
	delete j;
}