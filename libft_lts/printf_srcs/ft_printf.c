/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:32:29 by jinwoole          #+#    #+#             */
/*   Updated: 2022/03/21 19:38:49 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_percent(void)
{
	write(1, "%", 1);
	return (1);
}

int	specify_format(va_list ap, const char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_put_char(va_arg(ap, int));
	else if (format == 's')
		print_length += ft_put_str(va_arg(ap, char *));
	else if (format == 'p')
		print_length += ft_print_ptr(va_arg(ap, unsigned long long));
	else if (format == 'd')
		print_length += ft_put_nbr(va_arg(ap, int));
	else if (format == 'i')
		print_length += ft_put_nbr(va_arg(ap, int));
	else if (format == 'u')
		print_length += ft_put_unsigned(va_arg(ap, unsigned int));
	else if (format == 'x')
		print_length += ft_put_x(va_arg(ap, unsigned int), format);
	else if (format == 'X')
		print_length += ft_put_x(va_arg(ap, unsigned int), format);
	else if (format == '%')
		print_length += ft_put_percent();
	return (print_length);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	ap;
	int		print_length;

	i = 0;
	print_length = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			print_length += specify_format(ap, str[i + 1]);
			i++;
		}
		else if (str[i] == '\\' && str[i + 1] == 'n')
		{
			write(1, "\n", 1);
			i++;
		}
		else
			print_length += ft_put_char(str[i]);
		i++;
	}
	va_end(ap);
	return (print_length);
}
