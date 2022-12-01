/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:12:52 by eperaita          #+#    #+#             */
/*   Updated: 2022/08/15 19:57:30 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <dirent.h>

//CD_BUILTING -> Gets the current path and goes to $HOME (if has no arg)
//or to GET_NEW_VARS with the correct path as an arg. 
	//RETURN_ERROR -> Has not found HOME (FT_PRINT_RETURN)
	//GET_NEW_VARS -> Sets new PWD and sends new_vars to MOM_BUILTINGS 
	//CD_BUILTIN_ERROR -> Can't opendir or OLD_PWD not set (FT_PRINT_RETURN)
//FT_PRINT_RETURN -> Prints error and return (no exit) 

static char	**ft_print_return(int err, t_shell *shell)
{
	ft_putstr_fd("Pink peanuts:", 2);
	ft_putstr_fd(strerror(err), 2);
	ft_putstr_fd("\n", 2);
	shell->status_builtin = 1;
	return (NULL);
}

static int	cd_builtin_error(char *command_split, int err, t_shell *shell)
{
	if (command_split[0] == '-') 
	//문제 : cd - 하고 아무것도 없을때 나오는게 아니라, cd ---했을때 이게 뜬다.
	//그래서 제대로 작동되게 해야한다. 그래서, 플래그로 'cd -'일 경우 이 if문을 작동시키면 잘 된다.
	//shell을 - 확인하는 함수로 받아와서 하면 된다. special_path에 int flag로 shell->check를 받아와서 플래그를 올려준다.
	//shell->cd_flag로 받아왔다. 바부 계속 초기화되면 안되지
	{
		ft_putstr_fd("Pink peanuts: OLDPWD not set\n", 2);
		shell->status_builtin = 1;
		return (1);
	}
	if (!opendir(command_split) || (shell->my_pro->nbr_process == 1 
			&& chdir(command_split) != 0)) //opendir 실패하거나, (nbr process가 1이면서 chdir이 실패하면)
	//만약, 파이프가 하나 더 있다면, 앞의 오류와는 상관없이 그 뒤의 파이프 결과는 나온다. cd lfkslfj || echo "hello"
	{
		ft_print_return(err, shell);
		return (1);
	}
	return (0);
}

/*
	기존에 환경변수에서 받아온 PATH를 초기화한다. cd 했으니 이제 PATH가 달라졌을 수 있다
	그 다음 new_vars(pwd)도 다시 설정한다.
	new_vars 0번에는 old, 1번에는 새로운거, 2번은 NULL	
*/
static char	**get_new_vars(char **new_vars, char *str_path)
{
	char	path[1024];

	ft_free(str_path);
	str_path = ft_strdup(getcwd(path, 1024));
	new_vars[1] = ft_strjoin("PWD=", str_path);
	new_vars[2] = NULL;
	ft_free(str_path);
	return (new_vars);
}
/*
	HOME을 이상하게 설정해놔서 홈을 못여는 상황 HOME=1293u90123 일때, 적절한 오류를 내뱉는다.
	
*/
static char	**return_error(t_shell *shell, char **env, int a)
{
	if (!opendir(&env[a][5]))
		return (ft_print_return(errno, shell));
	if (shell->my_pro->nbr_process == 1 && chdir(&env[a][5]) != 0)
		return (ft_print_return(errno, shell));
	return (NULL);
}


//new_vars = cd_builtin((*shell)->my_env->env, &(*shell)->my_pro->child[id].command_split[1], new_vars, (*shell)); 

//CD_BUILTING -> Gets the current path and goes to $HOME (if has no arg)
//or to GET_NEW_VARS with the correct path as an arg. 
	//RETURN_ERROR -> Has not found HOME (FT_PRINT_RETURN)
	//GET_NEW_VARS -> Sets new PWD and sends new_vars to MOM_BUILTINGS 
	//CD_BUILTIN_ERROR -> Can't opendir or OLD_PWD not set (FT_PRINT_RETURN)


/*
	cd_builtin(여기서 받는 command_split은 cd 다음에 들어오는 단어 딱 하나)
	path의 길이는 char 1024개가 끝이다.
*/
char	**cd_builtin(char **env, char **command_split,
		char **new_vars, t_shell *shell)
{
	int		a;
	char	path[1024]; 
	char	*str_path;

	/*
		1. 현재 경로의 절대경로(getcwd)를 Path에 저장한다.
		2. new_vars를 "OLDPWD=" 환경변수에 저장한다.
	*/
	str_path = ft_strdup(getcwd(path, 1024)); 
	new_vars[0] = ft_strjoin("OLDPWD=", str_path);
	/*
		command_split이 없다면 = cd만 딱 쳤으면 home으로 가야한다.
		그런데 home이 없다? 그러면 에러
	*/
	if (!command_split[0])
	{
		a = -1;
		while (env[++a])
		{
			if (!ft_strncmp(env[a], "HOME=", ft_strlen("HOME=")))
				return (return_error(shell, env, a));
		}
	}
	/*
		cd ~ 와 - 명령어를 처리해야 한다.
		special_paths에서 적합한 경로를 넣어준다.
	*/
	else
	{
		command_split[0] = special_paths(env, command_split);
		if (cd_builtin_error(command_split[0], errno, shell))
			return (NULL);
	}
	/*
		결과가 어떻게 되든, 처리한 것을 기반으로 
		new_vars 0번에는 oldpwd, 1번에는 새로운거, 2번은 NULL인 이차원배열을 리턴한다
	*/
	return (get_new_vars(new_vars, str_path));
}
