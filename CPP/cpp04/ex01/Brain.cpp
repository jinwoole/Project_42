#include "Brain.hpp"
#include <iostream>

Brain::Brain()
{
	std::cout << "Brain constructed" << std::endl;
}

Brain::Brain(const Brain& other)
{
	int i = 0;

	while (i < 100)
	{
		ideas[i] = other.ideas[i];
		i++;
	}
	std::cout << "Brain copied" << std::endl;
}

Brain& Brain::operator=(const Brain& other)
{
	int i = 0;

	while (i < 100)
	{
		ideas[i] = other.ideas[i];
		i++;
	}
	std::cout << "Brain assigned by =" << std::endl;
	return *this;
}

Brain::~Brain()
{
	std::cout << "Brain destructed" << std::endl;
}

std::string Brain::getFirstIdea()
{
	return ideas[0];
}

void Brain::setFirstIdea(const std::string& idea)
{
	ideas[0] = idea;
}