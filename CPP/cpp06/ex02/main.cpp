#include "Base.hpp"

Base	*generate(void)
{
	Base*	ret;

	srand(time(NULL));
	int i = rand() % 3;
	switch (i)
	{
		case 0:
			ret = new A();
			break;
		case 1:
			ret = new B();
			break;
		case 2:
			ret = new C();
			break;
	}
	return ret;
}

//다운캐스팅 할때 자료형이 다르면 NULL 반환한다.
void	identify(Base* p)
{
	std::cout << "Identify *" << std::endl;
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
}

//레퍼런스는 NULL이 없으니 그대로 하니 안되네. 이 친구들은 오류를 내보낸다.
void	identify(Base& p)
{
	A a;
	B b;
	C c;

	std::cout << "Identify &" << std::endl;
	try 
	{
		a = dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
	} 
	catch (std::exception & e) 
	{
		try 
		{
			b = dynamic_cast<B&>(p);
			std::cout << "B" << std::endl;
		} 
		catch (std::exception & e) 
		{
			try 
			{
				c = dynamic_cast<C&>(p);
				std::cout << "C" << std::endl;
			} 
			catch (std::exception & e)
			{
			}
		}
	}
}

int main(void)
{
	Base *p;

	p = generate();
	identify(p);
	identify(*p);
}
