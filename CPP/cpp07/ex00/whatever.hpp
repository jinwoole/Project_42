#ifndef TEMPLATE
#define TEMPLATE

#include <iostream>

template <typename T>
void	swap(T& a, T& b)
{
	T temp;
	temp = b;
	b = a;
	a = temp;
}

template <typename T>
T	min(T const& a, T const& b)
{
	if (a < b)
		return a;
	else
		return b;
}

template <typename T>
T	max(T const& a, T const& b)
{
	if (a > b)
		return a;
	else
		return b;
}

#endif