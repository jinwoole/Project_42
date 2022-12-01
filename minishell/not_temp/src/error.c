/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:16:54 by zcanales          #+#    #+#             */
/*   Updated: 2022/08/17 14:25:27 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//CHECK_ERROR -> Handle the error and prints and RETURN
	//THREE_BRACKET_CHECK -> <<<
	//BRACKETS_CHECK -> |<
	//is_OPEN_QUOTE -> open quotes
	//(error_2.c)
//STATUS_ERROR -> Prints the error in str an EXIT

static int	three_brackets_check(char *line, char c, int *i)
{
	if (line[*i + 1] && line[*i + 1] == c)
	{
		if (line[*i + 2] && line[*i + 2] == c)
		{
			ft_putstr_fd("Pink peanuts:", 2); 
			ft_putstr_fd(" Syntax error near unexpected token 'newline'\n", 2);
			return (1); //syntax는 소문자여야한다.
		}
		*i += 1;//이 사람들은 천재다.
	}
	*i += 1;
	return (0);
}

/*
	char c에는 '<'와 '>'가 각각 들어와서 확인한다. <|, |<는 정상적으로 나오네? >|도 그렇고? 이건 어디서 처리하지? 이게 이거 아닌가?
	1. 브라켓이 3개 있나요?
	2. 브라켓 다음에 공백을 제외하고 '\0' > < | 등이 있으면 터진다. bash와 동일
*/
static int	brackets_check(char *line, char c)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == c)
		{
			if (three_brackets_check(line, c, &i))
				return (1);
			while (line[i] && line[i] == ' ' )
				i++; 
			if (line[i] == '\0' || line[i] == '<' || line[i] == '>'
				|| line[i] == '|') 
			{
				ft_putstr_fd("Pink peanuts:", 2);
				ft_putstr_fd("Syntax error near unexpected token 'newline'\n",
					2); 
				return (1);
			}
		}
	}
//근데 여긴 분기가 없다. 원본은 분기마다 newline이 아니라 > < 등 나온다. 원본하곤 다르다.
//정상적으로 <<만 있으면, newline 아니면 잘못입력된 < 등이 나온다. 그러니까, bash로 시연하지 말고 그냥 설명하자.
	return (0);
}

/*
	is_OPEN_QUOTE -> " " '' 뭐 이런게 열려있나요?

	check_quotes -> 다음 " 혹은 '까지 인덱스를 옮긴다
	i == '\0'이라는 말은, 닫혀있지 않았다는 말.
*/
static int	is_open_quote(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		check_quotes(line, &i);
		if (line[i] == '\0')
		{
			ft_putstr_fd("Pink peanuts:", 2);
			ft_putstr_fd(" Syntax error, unclosed quotes\n", 2);
			return (1); 
		}
	}
	return (0);
	//결과 문구가 원본과 다소 다를수는 있다. 하지만 서브젝트와 평가표에 근거할때, 잘 체크만 하면 그만이지.
}

/*
	check_line_empty : 라인에 공백밖에 없나요?
	brackets_check <, > : 리디렉션 다음에 이상한 것들이 있나요?
	is_open_quote : 따옴표가 잘 닫혀 있나요?
	check_two_pipe : || 를 쓰고 있나요?
*/
int	is_line_error(char *line)
{
	if (is_null_pipe(line))
		return (1);
	if (is_line_empty(line))
		return (1);
	if (is_open_quote(line))
		return (1);
	if (check_two_pipe(line))
		return (1);
	if (brackets_check(line, '<'))
		return (1);
	if (brackets_check(line, '>'))
		return (1);
	return (0);
}

void	status_error(char *str, int err)
{
	ft_putstr_fd("Pink peanuts: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(err);
}
