#include "Class.hpp"

Person::Person(int id)
{
	this->_id = new int(id);
}

Person::Person(const Person& other)
{
//	this->_id = other._id;
	this->_id = new int(*other._id);
}

Person::~Person()
{
	if (_id)
	{
		delete _id;
	}
	std::cout << "The Person is dead" << std::endl;
}

void Person::setName(int id)
{
	*this->_id = id;
}

void Person::showInfo()
{
	std::cout << "The ID is " << *this->_id << std::endl;
}
