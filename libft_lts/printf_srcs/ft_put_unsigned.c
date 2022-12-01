/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:47:16 by jinwoole          #+#    #+#             */
/*   Updated: 2022/02/04 12:01:45 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_num_len(unsigned	int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

char	*ft_unsigned_itoa(unsigned int n)
{
	char	*str;
	int		i;

	i = ft_num_len(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == 0)
		return (0);
	str[i] = '\0';
	while (n != 0)
	{
		str[i - 1] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	return (str);
}

int	ft_put_unsigned(unsigned int n)
{
	int		len;
	char	*num;

	len = 0;
	if (n == 0)
		len += write(1, "0", 1);
	else
	{
		num = ft_unsigned_itoa(n);
		len += ft_put_str(num);
		free(num);
	}
	return (len);
}
