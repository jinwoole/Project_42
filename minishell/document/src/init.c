/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:48:17 by zcanales          #+#    #+#             */
/*   Updated: 2022/08/16 12:41:58 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	get_environment	: main에서 받은 **env을 my_env구조체에 집어넣는다.
*/
void	get_environment(t_env *my_env, char **env)
{
	char	*path;
	char	*temp;
	int		i;

	/*
		env(main env)가 몇 개 있는지 세서, my_env를 같은 크기로 만든다.
	*/
	i = -1;
	while (env[++i])
		continue ;
	my_env->env = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!my_env->env)
		status_error(strerror(errno), errno);

	/*
		my_env의 env에 main env를 한줄씩 넣어준다.
	*/
	i = -1;
	while (env[++i])
		my_env->env[i] = ft_strdup(env[i]);
	my_env->env[i] = NULL;

	/*
		PATH 환경변수 정보를 my_env에 넣는다.
		: 기준으로 스플릿 한 이유는, : 기준으로 명령이 실행될 수많은 경로들이 있으니 그렇다.
	*/
	path = getenv("PATH"); //PATH를 이렇게 가져온거다.
	my_env->paths = ft_split(path, ':'); 

	/*
		위에서 PATH가져오면 완전한 경로가 아니다. :가 있던 자리에 /를 넣어야 완전한 경로가 된다.
		위에서 스플릿으로 받아온 버전 : /Users/lee/.yarn/bin
		아래에서 / 붙인 버전 : /Users/lee/.yarn/bin/
	*/
	i = 0;
	while (my_env->paths[i])
	{
		temp = ft_strjoin(my_env->paths[i], "/");
		free(my_env->paths[i]);
		my_env->paths[i] = temp;
		i++;
	}

	/* 
		home을 가져온다. dup하면 malloc까지 자동으로 되니 이렇게 한다. 
	*/
	my_env->home = ft_strdup(getenv("HOME"));
}

//============================================================================//


/*
	init: 쉘 구조를 초기화하고 정보를 집어넣는다.
*/
void	init(t_shell **shell, char **env)
{
	/*
		메모리 할당 및 초기화
	*/
	*shell = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (!(*shell))
		status_error(strerror(errno), errno);
	(*shell)->my_env = (t_env *)ft_calloc(sizeof(t_env), 1);
	(*shell)->my_pro = (t_pro *)ft_calloc(sizeof(t_pro), 1);
	if (!(*shell)->my_env || !(*shell)->my_pro)
		status_error(strerror(errno), errno);

/*
	get_environment	: main에서 받은 **env을 my_env구조체에 집어넣는다.
*/
	get_environment((*shell)->my_env, env);
}
