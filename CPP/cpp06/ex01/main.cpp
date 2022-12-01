#include <iostream>

typedef struct Data //데이터... 구조
{
	std::string data;
} Data;

//pointer를 가져다가 uintptr_t로 바꿔주어야 한다. 정수 포인터 주소를 저장 그런데 이상한 포인터도 저장된다.
uintptr_t serialize(Data* ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}

//uintptr_t를 가져다가 다시 Data*로 바꿔주어야 한다.
Data* deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data*>(raw);
}

int main(void)
{
	Data test;

	test.data = "Hello this is data";

	uintptr_t a;
	Data *b;

	a = serialize(&test); //데이터 오브젝트에 serialize하고
	b = deserialize(a); //그 값을 다시 deserialize

	std::cout << a << std::endl;
	std::cout << &test << std::endl;

	std::cout << &test << std::endl;
	std::cout << b << std::endl;

	std::cout << test.data << std::endl;
	std::cout << b->data << std::endl;

	//뭐 했다가 복구해보면 같다.

	return (0);
}
