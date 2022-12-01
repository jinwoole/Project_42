/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:44:11 by eperaita          #+#    #+#             */
/*   Updated: 2022/08/15 10:09:04 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//(error.c) -- check_error()
	//CHECK_TWO_PIPE -> ||
//CHECK_EMPTY_PIPE -> |  |
//CHECK_NULL_PIPE -> |
//CHECK_LINE_EMPTY
//PRINTF_ERROR -> Another error handler with print and set status


/*
	check_two_pipe : 우리는 보너스를 안하기 때문에, or도 받아주면 안된다. ||
	check_quotes -> " || " 이렇게 들어온건 or이 아니라 문자열이다. 만약 "를 만난다면 넘겨야 한다.
*/
int	check_two_pipe(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		check_quotes(line, &i);
		if (line[i] == '|' && line[i + 1] && line[i + 1] == '|')
		{
			ft_putstr_fd("Pink peanuts: 2 pipes are not allowed\n", 2);
			return (1);
		}
	}
	return (0);
}

/*
	check_empty_pipe -> 파이프가 비었나요? 예(1) 아니오(0)
	char **order = 스플릿을 해서, 파이프 기준으로 끊긴 명령
*/
int	check_empty_pipe(char **orders)
{
	int	i;
	int	j; //왜 j i 로 쓰는거야
/*
	첫번째 order 덩어리부터 시작해서,
	스페이스가 있다면 쭉 넘어간다. 단어가 있는데, 그게 스페이스면 넘어가야지
	그런데, 끝까지 가고보니 남은게 널밖에 없으면, | |은 빈거다.
*/
	j = -1;
	while (orders[++j])
	{
		i = -1;
		while (orders[j][++i] && orders[j][i] == ' ')
			continue ;
		if (orders[j][i] == '\0') 

		{
			ft_putstr_fd("Pink peanuts:", 2);
			ft_putstr_fd(" Syntax error near unexpected token '|'\n", 2);
			return (1);
		}
	}
	return (0);
}

/*
	check_null_pipe -> 파이프가 딱 하나만 나올 경우 | 오류
*/
int	check_null_pipe(char *line)
{
	int	i;
	/*
		1. 공백이 좀 있고 그 다음 |가 나오거나
		2. 처음에 뜬금없이 |가 나오고 바로 끝나버리면
		그렇다면 그 뒤에 뭐가 있든지간에 해당 오류문구를 return해야한다.
	*/
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		ft_putstr_fd("Pink peanuts:", 2);//fd2 = stderr
		ft_putstr_fd(" Syntax error near unexpected token '|'\n", 2);
		return (1);
	}

	//예를들어, echo | 같이 처음에 뭐 있고 끝에 빈 파이프만 나오고 종료되는 경우 이 경우가 작동된다. 이거 없으면 작동 안된다.
	i = -1;
	while (line[++i])
	{
		if (line[i] == '|' && line[i + 1] == '\0')
		{
			ft_putstr_fd("Pink peanuts:", 2); 
			ft_putstr_fd(" Syntax error near unexpected token '|'\n", 2); 
			return (1);
		}
	}
	/*
		평가시 절대 명령어 뒤에 | 바로 붙이지 말 것.
		파이프만 딱 입력할때하고, 파이프 입력하고 그 뒤에 뭐가 있을때만 보여주자.
		ls|은 bash에서 작동한다. echo "e"| 뭐 이거 해도 하지만 여기선 작동하지 않는다.
	*/
	return (0);
}

/*
	잘랐을때 아무것도 없다 == 스페이스만 있다 == 비었다
	비었나요? (1)네! (0)아니오!
*/
int	check_line_empty(char *line) //
{
	char	*new;

	new = ft_strtrim(line, " ");
	if (new[0] == '\0')
	{
		ft_free(new);
		return (1);
	}
	ft_free(new);
	return (0);
}

void	printf_error(char *s, int err, t_shell *shell)
{
	ft_putstr_fd("Pink peanuts: '", 2);
	ft_putstr_fd(s, 2);
	if (err == 1)
		ft_putstr_fd("' not a valid identifier\n", 2);
	if (err == 2)
	{
		ft_putstr_fd("': Command not found\n", 2);
		err = 1;
	}
	if (err == 3)
	{
		ft_putstr_fd(": too many arguments\n", 2);
		err = 1;
	}
	shell->status_builtin = err;
}
