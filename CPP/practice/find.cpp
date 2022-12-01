#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
	int myints[] = {10, 20, 30, 40};
	int* p;

	p = std::find(myints, myints + 4, 30);
	
	std::cout << *p << std::endl;
}