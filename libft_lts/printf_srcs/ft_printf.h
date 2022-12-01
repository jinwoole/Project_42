/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:31:50 by jinwoole          #+#    #+#             */
/*   Updated: 2022/02/04 11:51:32 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "stdarg.h"
# include "unistd.h"
# include "stdlib.h"

int		ft_printf(const char *str, ...);
int		specify_format(va_list ap, const char format);
int		ft_put_char(int c);
int		ft_put_str(char *str);
int		ft_ptr_len(unsigned long long num);
void	ft_put_ptr(unsigned long long num);
int		ft_print_ptr(unsigned long long ptr);
char	*ft_itoa(int n);
int		ft_put_nbr(int n);
int		ft_num_len(unsigned	int num);
char	*ft_unsigned_itoa(unsigned int n);
int		ft_put_unsigned(unsigned int n);
int		ft_x_len(unsigned int num);
void	ft_print_x(unsigned int num, const char format);
int		ft_put_x(unsigned int num, const char format);

#endif