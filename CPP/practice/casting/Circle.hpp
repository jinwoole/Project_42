#include <iostream>
#include <string>

class Circle
{
	public:
		int radius;
	public:
		Circle();
		void setRadius(int radius);
		void showRadius();
};

class Pizza : public Circle
{
	public:
		Pizza();
		double getArea();
};

class NonPizza : public Circle
{
	private:
		int two;
	public:
		NonPizza();
		void crazyRadius();
		void settwo(int a);
		void showtwo();
};