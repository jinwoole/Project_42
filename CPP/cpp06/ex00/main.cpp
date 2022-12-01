#include "Conversion.hpp"


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: Put 1 argument." << std::endl;
		return 1;
	}
	std::cout << std::fixed; //42.0이 42로 나온다. 그럼 나오게 하면 된다
	std::cout.precision(1);

	Conversion origin(argv[1]);

	

	origin.print_char();
	origin.print_int();
	origin.print_float();
	origin.print_double();
	return 0;
}
