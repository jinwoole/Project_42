/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:49:32 by zcanales          #+#    #+#             */
/*   Updated: 2022/08/12 12:25:07 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_freepointer(char **p, int *num_arrays)
{
	int	i;

	i = 0;
	while (i < (*num_arrays + 1))
	{
		free(&p[i]);
		i++;
	}
	free(p);
	return (0);
}

char	**ft_fill(char **p, char *s, char c, int *num_arrays)
{ //s는 line. 
	int		a;
	int		i;
	size_t	start;

	i = 0;
	a = 0;
	while (s[i] && a < *num_arrays)
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
			{
				check_quotes(s, &i); //만약 쌍따옴표가 있으면, 그 이후로 가야한다. 그리고도 계속 가서
				//결국 i를 가져오겠지.
				i++;
			}
			p[a] = ft_substr(s, start, i - start); //s에서 start부터 파이프 전까지 끊어준다.
			if (!p[a])
				return (ft_freepointer(p, num_arrays));
			a++; //그 다음 a++ p는 이중배열이니깐, 2차원만큼 더 해줘야한다.
		}
		if (s[i] == c)
			i++;
	}
	return (p);
}

void	ft_num_arrays(char *s, char c, int *nbr_array)
{//numarray는 자른 개수로 추정되는데,
	int	i;

	*nbr_array = 1;
	i = -1;
	while (s[++i])
	{
		check_quotes(s, &i);
		if (s[i] == c)
		{
			if (s[i + 1] && s[i + 1] == c && c != 32) //왜 여기서 i++가 되는거지?
			//전에 만들어놓고 안없앴을 가능성이 있다. 적어도, 중간의 더블파이프는 아니 애초에
			//알고보니 스페이스 쓰는 사례도 있다. 
			//정답: 리디렉션 2개 쓰는 사례가 있다. 그땐 바로 넘어가야 한다. 그러니까 +1이 되지 않게 하기 위해서
			//넘어가야 한다. c가 < > 둘 중 하나이거나로 해도 무방할 것 같다.
			//마지막 32를 바꾸면, < > 부분에서 터진다. 심지어 < >로 해도 터진다.
				i++;
			*nbr_array += 1; //파이프가 있으면 2개 된다.
		}
	}
}

char	**ft_split_2(char const *s, char c, int *nbr_array)
{
	char	**p;

	if (!s)
		return (0);
	ft_num_arrays ((char *)s, c, nbr_array);
	p = (char **)ft_calloc(sizeof(char *), (*nbr_array + 1));
	if (!p)
		status_error(strerror(errno), errno);
	p = ft_fill(p, (char *)s, c, nbr_array);
	if (c != '|' && c != 32)
		*nbr_array = *nbr_array - 1; //리디렉션일 경우는 포크를 2개 할 필요가 없어진다.
		//이 부분은 child pork에서 더 정확히 확인해봐야 한다. 설명이 정확히 안된다.
	return (p);
}
