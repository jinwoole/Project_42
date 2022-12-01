#include "Harl.hpp"

int main(int argc, char **argv)
{
	Harl harl;


    if (argc == 2)
    {
        harl.complain(argv[1]);
        return 0;
    }
    std::cout << "Too many parameters" << std::endl;
    return 1;
}