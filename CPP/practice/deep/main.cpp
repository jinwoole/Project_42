#include "Class.hpp"

int main(void)
{
	Person a(1);
	Person b(a);

	a.showInfo();
	b.showInfo();
	a.setName(3);

	a.showInfo();
	b.showInfo();

}