#include "iostream"


int ft_sum(int a, int b)
{
	return a + b;
}

class temp{
	public:
		int ft_sum(int a, int b) {
			return a + b;
		}
};


int main(void)
{

	int (*pf)(int, int) = ft_sum;
	temp tmp;

	int(temp::*fs)(int, int) = &temp::ft_sum;

	std::cout << pf(4, 5) << std::endl;
	std::cout << (tmp.*fs)(4,5) << std::endl;
}