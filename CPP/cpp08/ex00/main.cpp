#include "easyfind.hpp"
#include <vector>
#include <iostream>
#include <string>

int main(void)
{
	int Array[] = {1, 2, 3, 4, 5, 6, 7};
	std::vector<int> intVector(Array, Array + 7);

	if (easyfind(intVector, 8) == intVector.end())
	{
		std::cout << "Error : No such element" << std::endl;
	}
	else
	{
		std::cout << *easyfind(intVector, 4) << std::endl;
	}

	std::string strarray[] = {"간장", "공장", "공장장"};
	std::vector<std::string> strVector;

	strVector.push_back(strarray[0]);
	strVector.push_back(strarray[1]);
	strVector.push_back(strarray[2]);

	std::vector<std::string>::iterator iter;
	iter = strVector.begin(); //반복자 iter로 strVector시작점 가리키기

	for (iter = strVector.begin(); iter != strVector.end(); iter++)
	{
		std::cout << *iter << std::endl;
	}
}