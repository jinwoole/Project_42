#include "Animal.hpp"
#include <iostream>

Animal::Animal()
{
	std::cout << "[An animal started it's own journey]" << std::endl;
}

Animal::Animal(const Animal& other)
{
	this->type = other.type;
	std::cout << "An new animal is copied" << std::endl;
}

Animal& Animal::operator=(const Animal& other)
{
	this->type = other.type;
	return *this;
}

Animal::~Animal()
{
	std::cout << "An animal ended it's journey and faded away forever" << std::endl;
}

std::string Animal::getType() const
{
	return this->type;
}