/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:29:04 by jinwoole          #+#    #+#             */
/*   Updated: 2022/09/05 15:47:43 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

int main(void)
{
	std::string str = "HI THIS IS BRAIN";
	std::string *stringPTR = &str;
	std::string& stringREF = str;

	std::cout << "Address of string : " << &str << std::endl;
	std::cout << "Address of stringPTR : " << stringPTR << std::endl;
	std::cout << "Address of stringREF : " << &stringREF << std::endl;
	std::cout << "string : " << str << std::endl;
	std::cout << "value of stringPTR : " << *stringPTR << std::endl;
	std::cout << "value of stringREF : " << stringREF << std::endl;
}
