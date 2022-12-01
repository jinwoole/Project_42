#include "WrongCat.hpp"
#include <iostream>

WrongCat::WrongCat()
{
	type = "WrongCat";
	std::cout << "^^ The animal is constructed as a WrongCat." << std::endl;
}

WrongCat::WrongCat(const WrongCat& other)
{
	type = other.type;
	std::cout << "^^ The WrongCat is copied." << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& other)
{
	type = other.type;
	std::cout << "^^ The WrongCat is copied by operator =" << std::endl;
	return *this;
}

WrongCat::~WrongCat()
{
	std::cout << "^^ The WrongCat is destroyed." << std::endl;
}

void WrongCat::makeSound()
{
	std::cout << "WrongCat : Give me that tuna can, Human!" << std::endl;
}