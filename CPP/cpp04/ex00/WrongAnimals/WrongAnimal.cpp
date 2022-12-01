#include "WrongAnimal.hpp"
#include <iostream>

WrongAnimal::WrongAnimal()
{
	std::cout << "WrongAnimal constructed" << std::endl;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal destructed" << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
    std::cout << "WrongAnimal operator= called" << std::endl;
	type = other.type;
	return *this;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other)
{
	type = other.type;
	std::cout << "WrongAnimal is copied" << std::endl;
}

void WrongAnimal::makeSound()
{
	std::cout << "Hello I am a wrong animal, and cat shouldn't sound like this" << std::endl;
}

std::string WrongAnimal::getType()
{
	return type;
}