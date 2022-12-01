/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 08:57:21 by jinwoole          #+#    #+#             */
/*   Updated: 2021/12/05 09:20:01 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*src;
	int				i;

	ch = (unsigned char)c;
	src = (unsigned char *)s;
	i = 0;
	while (n--)
	{
		if (src[i] == ch)
			return ((void *)&src[i]);
		i++;
	}
	return (0);
}
