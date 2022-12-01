/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:54:51 by jinwoole          #+#    #+#             */
/*   Updated: 2022/08/26 14:54:55 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

int main(int argc, char **argv)
{
	int i;
    int j;

    if (argc == 1)
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
    i = 0;
    while (++i < argc) {
        j = 0;
        while (j < (int)strlen(argv[i])) {
            std::cout << (char)toupper(argv[i][j]);
            j++;
        }
    }
    std::cout << std::endl;
    return 0;
}
