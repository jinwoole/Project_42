#include "Harl.hpp"

int main(void)
{
	Harl harl;

	harl.complain("DEBUG");
	harl.complain("debug");
	harl.complain("INFO");
	harl.complain("WARNING");
	harl.complain("ERROR");
}