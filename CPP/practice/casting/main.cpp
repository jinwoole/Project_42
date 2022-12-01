#include "Circle.hpp"

int main() 
{
	Circle circle;
	circle.setRadius(10);
	circle.showRadius();

//=========================]

	Pizza cheesepizza;

	std::cout << "\ntime to casting\n" << std::endl; 

	Pizza *cDer = &cheesepizza;

	Circle* cBase = cDer; //업캐스팅 -> pizza객체를 부모클래스의 포인터로 가리킨다

	cBase->setRadius(100);
	std::cout << "치이즈피자 : " << cDer->getArea() << std::endl;
	//cBase->getArea(); //안됨
	
//	cDer = (Pizza*)cBase;
	cDer->setRadius(6); //여기선 cBase객체의 값이 바뀐다. 그러므로, cBase를 기반으로 다운캐스팅한 non의 radius값이 바뀐다
	cDer->showRadius();
	std::cout << "다운" << cDer->getArea() << std::endl; //이제 됨

	NonPizza* non = (NonPizza*)cBase; //base를 기반으로 다운캐스팅했다. 기본 클래스가 가리키는 객체를 파생 클래스의 포인터로 가리켜
	//파생 클래스의 함수를 쓸 수 있게 되었다.
	non->crazyRadius();
	non->setRadius(10);
	non->settwo(20);
	non->showtwo();

	cheesepizza.showRadius();

}
