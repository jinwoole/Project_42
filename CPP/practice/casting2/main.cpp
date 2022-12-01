#include <iostream>

int main()
{
	int a = 64;

	std::cout << a << std::endl;
	std::cout << static_cast<char>(a) << std::endl;

	int* ptr = new int(3);
	unsigned int myAddr = reinterpret_cast<unsigned int>(ptr);
	int* restoredAddr = reinterpret_cast<int*>(myAddr);

}