/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:32:36 by jinwoole          #+#    #+#             */
/*   Updated: 2021/12/15 14:01:23 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_checker(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	end;
	char	*result;

	i = 0;
	j = 0;
	end = ft_strlen(s1);
	while (s1[i] && set_checker(s1[i], set))
		i++;
	while (end > i && set_checker(s1[end - 1], set))
		end--;
	result = (char *)malloc(end - i + 1);
	if (result == 0)
		return (0);
	while (s1[i + j] && i + j < end)
	{
		result[j] = s1[i + j];
		j++;
	}
	result[j] = 0;
	return (result);
}
