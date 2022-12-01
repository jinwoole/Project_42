/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:12:38 by jinwoole          #+#    #+#             */
/*   Updated: 2021/12/15 20:11:50 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	split_num(char const *s, char c)
{
	int	num;
	int	i;

	if (s == 0)
		return (0);
	num = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != 0)
			num++;
		while (s[i] != c && s[i] != 0)
			i++;
	}
	return (num);
}

static char	**split_free(char **lst)
{
	free(lst);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**lst;
	int		word_len;
	int		i;

	lst = (char **)malloc((split_num(s, c) + 1) * sizeof(char *));
	if (s == 0 || lst == 0)
		return (split_free(lst));
	i = 0;
	while (*s)
	{
		while (*s == c && s != 0)
			s++;
		if (*s != 0)
		{
			if (ft_strchr(s, c) == 0)
				word_len = ft_strlen(s);
			else
				word_len = ft_strchr(s, c) - s;
			lst[i++] = ft_substr(s, 0, word_len);
			s += word_len;
		}
	}
	lst[i] = 0;
	return (lst);
}
