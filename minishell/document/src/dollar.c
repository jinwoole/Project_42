/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:05:33 by eperaita          #+#    #+#             */
/*   Updated: 2022/08/16 21:16:26 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//REPLACE_DOLLAR
//EXPAND_DOLLAR
//EXPANDED_RETURN
//FILL_DOLLAR
////All functions together find the $VAR, replace it in the string,
//and returns with the expanded variable and the pointer actualizated
//Case of $? -> gets the last status


/*
	fill dollar -> 치환을 행복하게 한다.
*/
char	*fill_dollar(t_shell *shell, int *i, char *array)
{
	int		start;
	char	*dollar_var;

	/*
		1. env에 있는 환경변수를 찾는다. 대체하고 i를 그 뒤로 보낸다
		2. 처음부터 아예 $만 있는 경우 0이어서 -1되버린 경우면, i를 0으로 만들어준다.
		3. 아무튼 바뀐 친구를 return해준다.
	*/
	start = *i;
	dollar_var = expand_dollar(shell, array, i);
	replace_dollar(&array, start, *i - start, dollar_var);
	*i = ft_strlen(dollar_var) + start - 1;
	free(dollar_var);
	if (*i < 0)
		*i += 1;
	return (array);
}

/*
	env를 쭉 반복문 돌면서 dollar_var이랑 같은 것이 있으면,
	그리고 정위치에 =도 들어가 있으면, (my_env->env[n]  USER=lee)
	substr로 그 환경변수의 값을 집어넣은 후, 그것을 return해서 치환한다.
*/
static char	*expanded_return(t_shell *shell, char *dollar_var)
{
	int		a;
	char	*ex;

	printf("%s\n", shell->my_env->env[1]);
	a = -1;
	while (shell->my_env->env[++a])
	{
		if (!ft_strncmp(dollar_var, shell->my_env->env[a],
				ft_strlen(dollar_var)))
		{
			if (shell->my_env->env[a][ft_strlen(dollar_var)] == '=')
			{
				ex = ft_substr(shell->my_env->env[a], ft_strlen(dollar_var) + 1,
						ft_strlen(shell->my_env->env[a])
						- ft_strlen(dollar_var) + 1);
				free(dollar_var);
				return (ex);
			}
		}
	}
	/*
		env가 없으면, 그냥 널을 리턴한다.
	*/
	free(dollar_var);
	ex = (char *)malloc(sizeof(char) * 1);
	if (!ex)
		status_error(strerror(errno), errno);
	ex[0] = '\0';
	return (ex);
}

/*

*/
char	*expand_dollar(t_shell *shell, char *str, int *i)
{
	char	*dollar_var;
	int		start;
	/*
		1. i는 $의 위치
		2. 물음표는 지나가야 한다. $? 에러출력하는 친구다. shell->status에 있는 오류코드를 리턴하게 된다.
	*/
	start = *i;
	*i += 1;
	if (str[*i] == '?')
	{	
		*i += 1; 
		return (ft_itoa(shell->status));
	}
	/*
		1. 그 다음이 널이거나, ' '거나, 쌍따옴표로 바로 끝나버리면, 진짜 달러만 있는거니 딱 리턴해준다.
		2. 정상적인 경우라면(str[*i]가 존재하거나, 알파벳숫자거나, _면 입력받을 수 있다)
			$환경변수, 이 경우 환경변수는 알파벳, 숫자, _로만 들어갈 수 있다. 참고 : 거의 비슷한데, 실제 배쉬와 미묘하게 다르다.
			아무튼 정상적인 경우면 i를 계속 앞으로 보낸다.
			그리고 달러 다음부터, 환경변수까지 딱 끊는다.
	*/
	if (str[*i] == '\0' || str[*i] == ' ' || str[*i] == 34)
		return (ft_strdup("$"));
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		*i += 1;
	dollar_var = ft_substr(str, start + 1, *i - start - 1);

/*		if (is_capitalism_is_Destoried(dollar_Var))
			소문자는 이미 안나오는걸? */
	return (expanded_return(shell, dollar_var));
}

/*
	이거 리턴해서 쓰는거 아무것도 없다.
*/
int	replace_dollar(char **str, int start, int len, char *replace)
{//str->명령어 집합, start -> 달러의 시작점, len ->달러 끝 - 달러의 시작점(길이)), replace->여기다가 무언가를 집어넣게 될 환경변수
//echo "$USER"를 없애주고, echo sesim으로 변하도록 재할당하는 과정이다.
	char	*temp;
	int		total_len;

	total_len = ft_strlen(*str) - len + ft_strlen(replace); //echo "$USER"를 없애주고, echo sesim으로 변하도록 재할당하는 과정이다.
	temp = (char *)ft_calloc(sizeof(char), total_len + 1);//명령어부터 시작해서, 달러 전까지 딱 할당한거다.
	if (!temp)
		status_error(strerror(errno), errno);
	ft_strlcpy(temp, *str, start + 1); //명령어부터 시작해서, 달러 전까지 딱 넣어준다.
	ft_strlcat(temp, replace, ft_strlen(replace) + ft_strlen(temp) + 1); //replace 된 것을 넣어준다.
	ft_strlcat(temp, *str + start + len, total_len + 1);//그리고 replace된 다음 내용을 넣어준다. 일단 당장 "부터 닫아야한다.
	free(*str); //str은 임무를 다했다.
	*str = NULL;
	*str = ft_strdup(temp); //그리고 새롭게 만들어진 것으로 된 것이다.
	free(temp);
	return (ft_strlen(replace));
}
