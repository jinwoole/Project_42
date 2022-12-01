#include "Contact.hpp"
#include "PhoneBook.hpp"

int main(void)
{
	PhoneBook book; //이 친구가 인스턴스. 만들어진 객체다.
	std::string buffer;

	while (1)
	{
		std::cout << "Command : ";
		getline(std::cin, buffer);
		if (buffer == "ADD")
		{
			book.AddContact();
		}
		else if (buffer == "SEARCH")
		{
			book.SearchContact();
		}
		else if (buffer == "EXIT")
		{
			break;
		}
		else
		{
			std::cout << "WRONG COMMAND : YOUR INPUT WILL BE DISCARDED" << std::endl;
		}
	}
	return 0;
}