/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:00:08 by zcanales          #+#    #+#             */
/*   Updated: 2022/08/16 21:07:20 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//FILL_QUOTE_DOLLAR -> Checks the string: decodes quotes and fills $VARS
	//FILL_QUOTE_UTILS
	//FILL_NEW_ARRAY
	//DECODE_QUOTES
	//CHECK_QUOTES

/*
	이건 "가 있다면, 다음 "까지 i를 보낸다. 혹은 equal?
	이 함수를 거친 후의 index는 다음 " 나 '를 가리켜야 한다.
	문자열 구간을 쭉 넘기는 방법으로 활용할 수도 있고, 닫히지 않은 것을 체크할 수도 있다.
	34 = "  39 = '
*/
int	check_quotes(char *s, int *index)
{
	int	i;
	int	equal; //이 equal은 왜있는거지? 그냥 return (0)해도 별 문제 없을것 같다.

	i = *index;
	equal = 0;
	if (s[i] == 34)
	{
		while (s[++i] && s[i] != 34)
			continue ;
	}
	else if (s[i] == 39)
	{
		while (s[++i] && s[i] != 39)
			continue ;
	}
	*index = i; 
	return (equal);
}

/*
	decode_quotes : 들어온 문자열에서 "환경변수"를 치환한다.
	i와 start는 모두 각 문자열 안에서 " 혹은 '를 만난 곳이다. 일단 i만 변화한다
*/
void	decode_quotes(t_shell *shell, char **str, int *i, int *start)
{
	int		dollar_pos;
	char	quote;
	char	*dollar_var;

	quote = *(*str + (*i)); //쌍따옴표나 따옴표 자리
	*i += 1;
	/*
		1. str + i가 존재하고, str + i가 quote(들어온 " or ')가 아닐때까지 반복한다.
			 만약 중간이 달러이고 "면('$user'는 환경변수 처리 안한다) 달러가 시작된 포지션을 설정한다.
		2. 그리고 "$명령어"를 치환할 변수값을 얻기 위해 expand_dollar를 사용한다.
		3. replace_dollar에서 그 dollar_var을 문자열에 집어넣는다. 
		4. While문 돌면서 그 다음 달러까지 또 가야하니깐, 대체한 다음으로 커서를 옮겨야 한다.
	*/
	while (*(*str + (*i)) && *(*str + (*i)) != quote) 
	{
		if (*(*str + (*i)) == '$' && quote == 34)
		{
			dollar_pos = *i;
			dollar_var = expand_dollar(shell, *str, i);
			replace_dollar(str, dollar_pos, *i - dollar_pos, dollar_var);
			*i = dollar_pos + ft_strlen(dollar_var) - 1;
			free(dollar_var);
		}
		*i += 1;
	}
	if(shell)
		shell->check = 1; //그 다음 shell->check ==1로 해준다. 이게 뭔지는 util에서 파악해야 한다.
	*start += 1;
}

char	*fill_new_array(char *array, int *i, char *new_array, int start)
{
	char	*temp_new_array;

	while (array[*i] && array[*i] != 34 && array[*i] != 39 && array[*i] != '$')
		*i += 1; //*i가 있고, 따옴표 아니고 달러 아니면, 앞으로 간다.
	if (array[*i] == '$' && (array[*i + 1] == '\0' || array[*i + 1] == ' ')) //이러면 그 다음에 $만 딱 나와야 한다. 아마도
		*i += 1;
 	//달러사인이 나오고, 그 다음이 널이거나 스페이스면 = 진짜 한 단어 끝날때까지 가면?
	temp_new_array = ft_substr_strjoin(array, new_array, start, *i);
	return (temp_new_array);
}

void	fill_quote_utils(int *ch, t_shell *shell, int *i)
{
	/*
	ch가 1이면(이 목적을 위해서만 입력받는다), 0으로 바꿔버린다.
		filename가공하는 부분엔 ch가 1로 들어간다.
	*/
	if (*ch == 1) 
		*ch = 0;
	if (shell->check)
		*i += 1;
	/*
	shell->chekc 1이면 i +=1
	shell이 있으면 shellcheck하고 함수가 종료되는데, 문자가 없으니 그러니까 i++이 없으니 종료되지 않는다.
	*/
}

/*
	fill_quote_dollar : 문자열을 스캔해서, 환경변수 표시가 있다면 치환해준다.
	1. clean_commands 함수에 사용된다. <command_split, 쉘, child의nbr_command, 2>
	2. filename가공하는 부분엔 ch가 1로 들어간다. ch는 여기서 ch=0하는거 말고 별게 없다.
*/
char	**fill_quote_dollar(char **array, t_shell *shell, int nbr_array, int ch) 
{ 
	int		a;
	int		i;
	int		start;
	char	**new_array;

	/*
		1. count_command 만큼 malloc을 해준다.
		2. ch가 2일때, command_split의 끝까지 스캔한다. /:/ ch가 1인 경우엔, fill_quote를 거치고, 한번만 돌고 끝난다.
			1. 문자열에 "나 ' 를 만난다면 -> echo "$USER" 따옴표 안에 있어도 bash의 마수를 피해가선 안된다. decode한다.
			2. 그냥 달러를 만난다면, fill_dollar로 치환 잘 해주면 된다.
			3. (1 or 2)를 거친 후, start부터, 지금까지 i로 읽은 곳까지 끊어서, new_array에 넣는다.
	*/
	a = -1;
	new_array = (char **)ft_calloc(sizeof(char *), nbr_array + 1);
	while (ch && array[++a])
	{
		i = 0;
		while (array[a][i])
		{
			start = i;
			if (array[a][i] == 34 || array[a][i] == 39)
				decode_quotes(shell, &array[a], &i, &start);
			else if (array[a][i] == '$')
				array[a] = fill_dollar(shell, &i, array[a]);
			new_array [a] = fill_new_array(array[a], &i, new_array[a], start); 
			fill_quote_utils(&ch, shell, &i);
			shell->check = 0; 
			//파이프가 없으면 그냥 끝나면 된다. 그런데, shell->check가 있으면, 한번 더 가서 이 반복문을 끝내라.
			//우린 shell->check = 0을 줄수 줄이기 위한 저 fill_quote_utils에 넣는다.
		}
	}
	new_array[nbr_array] = NULL;
	free_double(array, ch);

	return (new_array); 
	/* 
		command_split으로 다시 들어가는 경우, file_name_clean으로 들어가는 경우가 있다.
	*/
}
