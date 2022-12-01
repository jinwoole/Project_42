#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP
# include <iostream>
# include <string>
# include <iomanip>
# include "Contact.hpp"

class PhoneBook //이건 전화번호부를 추상화한 클래스
{
	private:
		Contact	contact[8];
		int		length;
		int		old;
		void	print_column(std::string _text);
		void	DisplayBook();
		void	DisplayRaw(int i);
        void	DisplayOneRaw(int i);
        void	DisplayInfo();
		void	DisplaySelected();
	public:
		PhoneBook() : length(0), old(0) {}
		void AddContact();
		void SearchContact();
};

#endif