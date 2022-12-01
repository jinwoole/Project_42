/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:26:34 by sesim             #+#    #+#             */
/*   Updated: 2022/08/11 23:28:32 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/libft_src/libft.h"
#include <stdio.h>
#include <errno.h>

void	get_environment(t_envs *cp_envs, char **env)
{
	char	*path;
	char	*tmp;
	int		i;

	i = -1;
	while (env[++i])
		continue ;
	cp_envs->env = ft_calloc(i + 1, sizeof(char *));
	if (!cp_envs->env)
		error_status(strerror(errno), errno);
	i = -1;
	while (env[++i])
		cp_envs->env[i] = ft_strdup(env[i]);
	cp_envs->env[i] = 0;
	path = getenv("PATH");
	cp_envs->paths = ft_split(path, ':');
	i = -1;
	while (cp_envs->paths[++i])
	{
		tmp = ft_strjoin(cp_envs->paths[i], "/");
		free(cp_envs->paths[i]);
		cp_envs->paths[i] = tmp;
	}
	cp_envs->home = ft_strdup(getenv("HOME"));
}

void	shell_init(t_shell **shell, char **env)
{
	*shell = ft_calloc(1, sizeof(t_shell));
	if (!(*shell))
		error_status(strerror(errno), errno);
	(*shell)->cp_envs = ft_calloc(1, sizeof(t_envs));
	if (!(*shell)->cp_envs)
		error_status(strerror(errno), errno);
	(*shell)->cp_pros = ft_calloc(1, sizeof(t_pros));
	if (!(*shell)->cp_pros)
		error_status(strerror(errno), errno);
	get_environment((*shell)->cp_envs, env);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell_init(&shell, env);
	create_terminal(shell);
}
