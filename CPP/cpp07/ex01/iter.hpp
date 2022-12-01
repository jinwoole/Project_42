#ifndef ITER
#define ITER

#include <iostream>

//address of array, length, function... 반복

template <typename T>
void	iter(T *arr, int length, void(*func)(T const&)) 
{
	for (int i = 0; i < length; i++)
		func(arr[i]);
}

#endif