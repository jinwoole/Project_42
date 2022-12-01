#include "Contact.hpp"
#include <iostream>
#include <string>

Contact::Contact(std::string first_name,
		std::string last_name,
		std::string nickname,
		std::string phone_number,
		std::string darkest_secret)
{
	this->first_name = first_name;
	this->last_name = last_name;
	this->nickname = nickname;
	this->phone_number = phone_number;
	this->darkest_secret = darkest_secret;
}

Contact::Contact()
{
	Contact("", "", "", "", "");
}

Contact::~Contact()
{
}

void Contact::FillContact()
{
	std::cout << "Enter [first name] : ";
	getline(std::cin, this->first_name);
	std::cout << "Enter [last name] : ";
	getline(std::cin, this->last_name);
	std::cout << "Enter [nickname] : ";
	getline(std::cin, this->nickname);
	std::cout << "Enter [phone number] : ";
	getline(std::cin, this->phone_number);
	std::cout << "Enter [darkest secret] : ";
	getline(std::cin, this->darkest_secret);

	std::cout << "Contact added" << std::endl;
}

std::string Contact::GetFirstName()
{
	return this->first_name;
}

std::string Contact::GetLastName()
{
	return this->last_name;
}

std::string Contact::GetNickName()
{
	return this->nickname;
}

std::string Contact::GetNumber()
{
	return this->phone_number;
}

std::string Contact::GetSecret()
{
	return this->darkest_secret;
}