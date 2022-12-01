#include "Cat.hpp"
#include <iostream>

Cat::Cat()
{
	catBrain = new Brain;
	this->type = "Cat";
	std::cout << "[A cat constructed]" << std::endl;
}

Cat::Cat(const Cat& other)
{
	catBrain = new Brain;
	this->type = other.type;
	std::cout << "A cat copied" << std::endl;
}

Cat& Cat::operator=(const Cat& other)
{
	if (catBrain)
		delete catBrain;
	catBrain = new Brain(*(other.getBrain()));
	this->type = other.type;
	std::cout << "A cat assigned by operator =" << std::endl;
	return *this;
}

Cat::~Cat()
{
	if (catBrain)
        delete catBrain;
	std::cout << "Some say, Cat has 9 lives. But the cat is destructed" << std::endl;
}

void Cat::makeSound() const
{
	std::cout << this->type << " : Give me the Tuna Can, Human!" << std::endl;
}

Brain* Cat::getBrain() const
{
    return catBrain;
}