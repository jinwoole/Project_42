#include "Circle.hpp"

void Circle::setRadius(int radius)
{
    this->radius = radius;
}

Circle::Circle()
{
	std::cout << "Circle constructor" << std::endl;
}

Pizza::Pizza()
{
	std::cout << "Pizza constructor" << std::endl;
}

NonPizza::NonPizza()
{
	std::cout << "NonPizza constructor" << std::endl;
}

void Circle::showRadius()
{
	std::cout << "Circle radius: " << this->radius << std::endl;
}

double Pizza::getArea()
{
	return radius * radius * 3.14;
}

void NonPizza::crazyRadius()
{
	std::cout << "=Hello? My name is " << radius << std::endl;
}

void NonPizza::settwo(int a)
{
	this->two = a;
}

void NonPizza::showtwo()
{
	std::cout << "NonPizza two: " << this->two << std::endl;
}