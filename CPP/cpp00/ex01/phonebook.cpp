#include "PhoneBook.hpp"
#include <sstream>

void	PhoneBook::AddContact()
{
	if (PhoneBook::length == 8)
	{
		Contact contact;
		contact.FillContact();
		PhoneBook::contact[old] = contact;
		PhoneBook::old++;
		if (PhoneBook::old >= 8)
			PhoneBook::old = 0;
	}
	else
	{
		Contact contact;
		contact.FillContact();
		PhoneBook::contact[length] = contact;
		PhoneBook::length++;
	}
}

void PhoneBook::print_column(std::string _text)
{
    // std::sew = 너비 설정
    // std::right = 오른쪽 정렬
    if (_text.length() <= 10)
        std::cout << std::right << std::setw(10) << _text;
    else
    {
        _text =  _text.substr(0,9) + ".";
        std::cout << std::right << std::setw(10) << _text;
    }
}

void	PhoneBook::DisplayRaw(int i)
{
	print_column(std::to_string(i));
	std::cout << "|";
	print_column(contact[i].GetFirstName());
	std::cout << "|";
	print_column(contact[i].GetLastName());
	std::cout << "|";
	print_column(contact[i].GetNickName());
	std::cout << "|";
	std::cout << std::endl;
}

void	PhoneBook::DisplayOneRaw(int i)
{
    print_column(std::to_string(i));
    std::cout << "|";
    print_column(contact[i].GetFirstName());
    std::cout << "|";
    print_column(contact[i].GetLastName());
    std::cout << "|";
    print_column(contact[i].GetNickName());
    std::cout << "|";
    print_column(contact[i].GetNumber());
    std::cout << "|";
    print_column(contact[i].GetSecret());
    std::cout << "|";
    std::cout << std::endl;
}

void	PhoneBook::DisplayInfo()
{
	print_column("index");
	std::cout << "|";
	print_column("first name");
	std::cout << "|";
	print_column("last name");
	std::cout << "|";
	print_column("nickname");
	std::cout << "|";
	std::cout << std::endl;
}

void	PhoneBook::DisplayBook()
{
	int i = 0;

	PhoneBook::DisplayInfo();
	while (i < PhoneBook::length)
	{
		PhoneBook::DisplayRaw(i);
		i++;
	}
}

void	PhoneBook::DisplaySelected()
{
	int				    index;
	std::string			input;
	std::stringstream	temp;

	std::cout << "Choose a contact to display: ";
	std::getline(std::cin, input);
	temp << input;
	temp >> index;
	if (temp.fail() || index < 0 || index > 7)
		std::cout << "Wrong index" << std::endl;
	else if (index >= PhoneBook::length)
		std::cout << "No such index" << std::endl;
	else
    {
        print_column("index");
        std::cout << "|";
        print_column("first name");
        std::cout << "|";
        print_column("last name");
        std::cout << "|";
        print_column("nickname");
        std::cout << "|";
        print_column("number");
        std::cout << "|";
        print_column("secret");
        std::cout << "|";
        std::cout << std::endl;
        DisplayOneRaw(index);
    }
}

void	PhoneBook::SearchContact()
{
	PhoneBook::DisplayBook();
	PhoneBook::DisplaySelected();
}

