#include "Dog.hpp"
#include <iostream>

Dog::Dog()
{
	this->type = "Dog";
	std::cout << "[A Dog constructed]" << std::endl;
}

Dog::Dog(const Dog& other)
{
	this->type = other.type;
	std::cout << "A Dog copied" << std::endl;
}

Dog& Dog::operator=(const Dog& other)
{
	this->type = other.type;
	std::cout << "A Dog assigned by operator =" << std::endl;
	return *this;
}

Dog::~Dog()
{
	std::cout << "We all want that our dog live with us forever. But we all have to face the cruel reality" << std::endl;
}

void Dog::makeSound() const
{
	std::cout << this->type << " : Bark! Bark!" << std::endl;
}
