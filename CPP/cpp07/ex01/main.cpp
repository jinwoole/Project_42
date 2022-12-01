#include "iter.hpp"

template <typename T>
void printanything(T const& element)
{
	std::cout << element << std::endl;
}

int main(void)
{
	std::string arr[4] = {"Hello", "this", "is", "iter"};

	iter(arr, 4, printanything);


	int arr2[1000];
	for (int i = 0; i <= 1000; ++i)
		arr2[i] = i;
	
	iter(arr2, 1001, printanything);
}