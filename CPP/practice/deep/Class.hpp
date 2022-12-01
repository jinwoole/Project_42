#include <iostream>
#include <string>

class Person
{
	private:
		int *_id;
	public:
		Person(int id);
		~Person();
		Person(const Person& other);

		void setName(int id);
		void showInfo();
};