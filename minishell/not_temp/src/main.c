/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:50:16 by zcanales          #+#    #+#             */
/*   Updated: 2022/08/17 13:41:44 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_mainenv(t_env *my_env, char **env)
{
	char	*path;
	char	*temp;
	int		i;

	i = -1;
	while (env[++i])
		continue ;
	my_env->env = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!my_env->env)
		status_error(strerror(errno), errno);
	i = -1;
	while (env[++i])
		my_env->env[i] = ft_strdup(env[i]);
	my_env->env[i] = NULL;
	path = getenv("PATH");
	my_env->paths = ft_split(path, ':');
	i = 0;
	while (my_env->paths[i])
	{
		temp = ft_strjoin(my_env->paths[i], "/");
		free(my_env->paths[i]);
		my_env->paths[i] = temp;
		i++;
	}
	my_env->home = ft_strdup(getenv("HOME"));
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	if (ac != 1)
	{
		printf("player: %s: No such file or directory\n", av[1]);
		return (1);
	}
	(void)av;
	shell = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (!(shell))
		status_error(strerror(errno), errno);
	(shell)->my_env = (t_env *)ft_calloc(sizeof(t_env), 1);
	(shell)->my_pro = (t_pro *)ft_calloc(sizeof(t_pro), 1);
	if (!(shell)->my_env || !(shell)->my_pro)
		status_error(strerror(errno), errno);
	get_mainenv((shell)->my_env, env);
	create_terminal(shell);
	return (0);
}
