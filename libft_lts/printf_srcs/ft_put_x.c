/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:49:27 by jinwoole          #+#    #+#             */
/*   Updated: 2022/02/04 12:04:59 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_x_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	ft_print_x(unsigned int num, const char format)
{
	if (num >= 16)
	{
		ft_print_x(num / 16, format);
		ft_print_x(num % 16, format);
	}
	else
	{
		if (num <= 9)
			ft_put_char((num + '0'));
		else
		{
			if (format == 'x')
				ft_put_char((num - 10 + 'a'));
			if (format == 'X')
				ft_put_char((num - 10 + 'A'));
		}
	}
}

int	ft_put_x(unsigned int num, const char format)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		ft_print_x(num, format);
	return (ft_x_len(num));
}
