/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:04:13 by jinwoole          #+#    #+#             */
/*   Updated: 2022/09/05 14:39:39 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void randomChump(std::string name)
{
	Zombie Chump(name); //함수 안에서 인스턴스가 역할을 다 하니, 스택영역에 생성해도 된다.
	Chump.announce();
}