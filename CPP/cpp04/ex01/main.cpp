#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

int main(void)
{
	const Animal* i = new Cat();
	const Animal* j = new Dog();

	Dog *a = (Dog *)j;
	std::cout << a->getIdea() << std::endl;
	a->setIdea("this");
	std::cout << a->getIdea() << std::endl;

	delete i;
	delete j;

	std::cout << "====================================================" << std::endl;

	Dog one;
	Dog two(one);
	Dog three;

	one.setIdea("No.1");
	std::cout << one.getIdea() << std::endl;
	std::cout << two.getIdea() << std::endl;
	
	three = one;

	std::cout << one.getIdea() << std::endl;
	std::cout << three.getIdea() << std::endl;
	one.setIdea("왈");
	std::cout << one.getIdea() << std::endl;
	std::cout << three.getIdea() << std::endl;
	
	std::cout << "====================================================" << std::endl;
}