/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 10:20:32 by jinwoole          #+#    #+#             */
/*   Updated: 2021/12/16 13:13:30 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i;
	size_t			j;
	unsigned char	*hay;
	unsigned char	*ndl;

	i = 0;
	hay = (unsigned char *)haystack;
	ndl = (unsigned char *)needle;
	if (needle[0] == '\0')
		return ((char *)hay);
	while (i < len && hay[i])
	{
		j = 0;
		while (hay[i + j] == ndl[j] && i + j < len)
		{
			j++;
			if (ndl[j] == '\0')
				return ((char *)&hay[i]);
		}
		i++;
	}
	return (0);
}
