/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:26:20 by eperaita          #+#    #+#             */
/*   Updated: 2022/08/15 20:54:44 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//GET_NEW_PATHS -> Cd builtin. Resets $PATH in env 
	//GET_NEW_PATHS_ELSE -> Aux function 
//GET_EXE_PATH -> ./ must go to execvue as command[0]
//SPECIAL_PATHS -> If the path is back or home

//////////////SPECIAL PATHS/////////////////

/*
	cd back or home일때 경로를 가지고 오게 된다.
	참고 : strncmp는 같으면 0 나온다.
*/
static char	*special_paths_back(char **env, char **command, char *find)
{
	int		a;
	char	*temp;
	char	*to_join;

	temp = NULL;
	a = -1;
	while (env[++a])
	{
		if (!ft_strncmp(env[a], find, ft_strlen(find)))
		{	
			/*
				일단 ~가 나오면 그 뒤를 쭉 복사한다. ~/philo 뭐 이렇게 할 수도 있으니.
				- 가 나오면 그냥 1만큼 할당해준다.
			*/
			if (command[0][0] == '~')
				temp = ft_strdup(&command[0][1]);
			else if (command[0][0] == '-')
				temp = (char *)ft_calloc(1, 1);
			/*
				env[a] 는 oldpath. 
				아무튼 이 시점에서 cd - 할때 OLDPWD=/USER/lee 이게 출력되고, ~하면 HOME=/USER/lee 뭐 대충 이게 들어간다.
				그리고 그걸 =하고 /까지 지나서, find, strlen부터 하면 다 지나치고, /USER/lee 이것만 남긴다.
			*/
			to_join = ft_strdup(&env[a][ft_strlen(find)]);
			ft_free(*command);
			/*
				아무튼 기존의 경로를 없애버린다음에, temp와 합친다. temp는 ~/philo 했을때, /philo
				그 결과, /USERS/sesim/philo/ 이렇게 완성된다.
			*/
			command[0] = ft_strjoin(to_join, temp);
			ft_free(temp);
			ft_free(to_join);
			return (command[0]);
		}
	}
	//while문을 다 돌았는데도 oldpwd가 없다면, printf로 bash와 같은 경보를 내보낼 수 있다. 
	//나오긴 나오는데, 이 분기가 다르다. oldpwd조차 없을땐 미니쉘에서 안뜬다.
	return (command[0]);
}

/*
	cd 물결 혹은 -를 처리한다.
	1. - 면 그냥 OLDPWD를 가져다가 넣어준다. oldpwd는 cd bulitin 시작하자마자 새로 저장해준다.
*/
char	*special_paths(char **env, char **command)
{
//	char	*temp;
//	char	*to_join;

//	if (ft_strcmp(command[0], "-"))
	if (command[0][0] == '-')
		return (special_paths_back(env, command, "OLDPWD="));
	else if (command[0][0] == '~')
		command[0] = special_paths_back(env, command, "HOME="); //home directory를 가져온다.
/*	if (command[0][0] == '~') 
	//근데 왜 else if 하고 또 똑같은건가? 그냥 합쳐도 되는거 아니냐? 안되네. 왜 따로한거지? 그냥 물결을 없애는건데?
	//special_paths_back을 지나고도, [0][0]이 ~인 경우가 있다는거지.
	{
		temp = ft_strdup(&command[0][1]); //~ 다음에 뭐가 있을 수 있다. ~/philosopher/philo 같은거
		ft_free(*command);
		to_join = ft_strdup(getenv("HOME"));
		command[0] = ft_strjoin(to_join, temp);
	} 
//일단 뭔지 모르겠지만, 없어도 작동한다
*/
	
	return (command[0]);
}

///////////////// -  "./" -  //////////////////
/*
 	./philo를 예를들어 입력했다고 한다면, 실행가능한 경로로 바뀌어야 한다.
	new_command는 이 경우 파일 이름만 뚝 잘라서 리턴하게 된다.
*/
char	*get_exe_path(t_shell *shell, char *command_split) 
{
	char	*new_command;
	/*
		1. **paths를 지우고 새로 할당한다
		2. philo가 들어가서 복사해주는데, 0부터 시작해서, 마지막 / 이전까지 불러온다. path[0]에 경로를 불러온다.
		3. new_command에는 실행할 파일 이름을 넣어준다.
	*/
	new_command = NULL;
	free_double(shell->my_env->paths, 2);
	shell->my_env->paths = (char **)ft_calloc(sizeof(char *), 2);
	if (!shell->my_env->paths)
		status_error(strerror(errno), errno);
	shell->my_env->paths[0] = ft_substr(command_split, 0, ft_strlen(command_split) - ft_strlen(ft_strrchr(command_split, '/')) + 1);
	/*
		/를 못찾았다면 command not found
	*/
	if (ft_strrchr(command_split, '/'))
		new_command = ft_strdup(ft_strrchr(command_split, '/') + 1); //복사해서, 
	else
		status_error("Command not found", 127);
	free (command_split);
	return (new_command);

	//path라는 곳에는 ./에서 .에 절대경로를 받아온다. ./minishell/pihlo/philo라면, ./minishell/pihlo/
	// 그리고 a.out자리엔, newcommand는 실행파일의 이름이 받아진다. 일단 그렇게 한다.
}

////////////////////////PATHS////////////////////
//GET_NEW_PATHS -> Cd builtin. Resets $PATH in env 
	//GET_NEW_PATHS_ELSE -> Aux function 
//GET_EXE_PATH -> ./ must go to execvue as command[0]


void	get_new_path_else(t_shell *shell)
{
	free_double(shell->my_env->paths, 2);
	shell->my_env->paths = (char **)ft_calloc(sizeof(char *), 1);
	if (!shell->my_env->paths)
		status_error(strerror(errno), errno);
}

void	get_new_paths(char **env, t_shell *sh) //1. 만약 export나 unset으로 path를 바꾸었으면, 다시 설정해야 한다.
{
	int		a;
	char	*temp;

	a = -1;
	while (env[++a])
	{
		if (!ft_strncmp(env[a], "PATH=", ft_strlen("PATH=")))
		{
			free_double(sh->my_env->paths, 2);
			sh->my_env->paths = ft_split(&env[a][ft_strlen("PATH=" - 1)], ':');
			break ;
		}
	}
	if (env[a] != NULL)
	{
		a = -1;
		while (sh->my_env->paths[++a])
		{
			temp = ft_strjoin(sh->my_env->paths[a], "/");
			free(sh->my_env->paths[a]);
			sh->my_env->paths[a] = temp;
		}
	}
	else //만약 끝까지 갔을때도 없으면,
		get_new_path_else(sh);
}
