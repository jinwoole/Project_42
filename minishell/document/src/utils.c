/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:39:56 by eperaita          #+#    #+#             */
/*   Updated: 2022/08/14 20:27:29 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//FT_SUB_JOIN -> Substr + Strjoin
//FREE_DOUBLE -> Free of double array
//FREELIST -> Free whole linked list
//CONVERT ARRAY TO STRING -> Returns a double array of 1 to char *
//FT_STRCMP_LEN -> Compares the len of a piece of 2 different strings

/*
	echo하고 달러표시 전에 이상한거 오면 잘라야하니 자른거다.
*/
char	*ft_substr_strjoin(char *to_sub, char *to_join, int start, int end)
{
	char	*real_temp;
	char	*temp;

	temp = ft_substr(to_sub, start, end - start);
	if (!to_join)
		real_temp = ft_strdup(temp);
	else
	{
		real_temp = ft_strjoin(to_join, temp);
		free(to_join);
	}
	free(temp);
	return (real_temp);
}

void	free_double(char **s, int check)
{
	int	i;

	i = -1;
	if (!s)
		return ;
	while (s[++i])
		ft_free(s[i]);
	if (check == 2)
	{
		ft_free(s);
		s = NULL;
	}
}

void	ft_freelist(t_list **head)
{
	t_list	*temp;

	if (!*head)
	{
		return ;
	}
	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		free (temp);
	}
	*head = NULL;
}

/*
	뭐라해야하냐, 진짜 그냥 바꿔준다.
*/
char	*convert_array_to_string(char **array)
{
	char	*string;

	string = NULL;
	if (array[0])
		string = ft_strdup(array[0]);
	free_double(array, 2);
	return (string);
}

int	ft_strcmp_len(char *env, char *var)
{
	int	len_1;
	int	len_2;

	len_1 = ft_strlen((char *)env)
		- ft_strlen(ft_strchr((char *)env, '='));
	len_2 = ft_strlen((char *)var)
		- ft_strlen(ft_strchr((char *)var, '='));
	if (len_1 == len_2 && !ft_strncmp((char *)var,
			(char *)env, len_1))
		return (1);
	return (0);
}
