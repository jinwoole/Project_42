#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <iostream>

class Contact {
	private:
		std::string	first_name;
		std::string last_name;
		std::string nickname;
		std::string phone_number;
		std::string darkest_secret;
	public:
		Contact(); //constructor
		Contact(std::string first_name, std::string last_name, std::string nickname,
		std::string phone_number, std::string darkest_secret); //생성자 초기화 방법 1

		void FillContact();
		std::string GetFirstName();
		std::string GetLastName();
		std::string GetNickName();
		std::string GetNumber();
		std::string GetSecret();

		~Contact(); // destructor
};

#endif