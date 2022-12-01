#include "Dog.hpp"
#include <iostream>

Dog::Dog()
{
	dogBrain = new Brain;
	this->type = "Dog";
	std::cout << "[A Dog constructed]" << std::endl;
}

Dog::Dog(Dog& other)
{
	dogBrain = new Brain(*(other.getBrain()));
	this->type = other.type;
	std::cout << "A Dog copied." << std::endl;
}

Dog& Dog::operator=(Dog& other)
{
	/*if (dogBrain)
		delete dogBrain;
	dogBrain = new Brain(*(other.getBrain()));*/
	dogBrain = other.dogBrain;
	this->type = other.type;
	std::cout << "A Dog assigned by operator =" << std::endl;
	return *this;
}

Dog::~Dog()
{
	delete dogBrain;
	std::cout << "We all want that our dog live with us forever. But we all have to face the cruel reality" << std::endl;
}

void Dog::makeSound() const
{
	std::cout << this->type << " : Bark! Bark!" << std::endl;
}

std::string Dog::getIdea()
{
	return this->dogBrain->getFirstIdea();
}

void Dog::setIdea(const std::string& idea)
{
	this->dogBrain->setFirstIdea(idea);
}

Brain* Dog::getBrain()
{
	return this->dogBrain;
}