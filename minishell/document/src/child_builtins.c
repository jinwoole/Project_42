/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:26:41 by zcanales          #+#    #+#             */
/*   Updated: 2022/08/14 19:46:58 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>

//CHECK_BUILTINS_CHILD -> Filter bultins. If it si a mom builtin (exit)
	//EXIT_BUILTIN__CHILD -> Exit the program and filter exit args
	//ENV_BU -> Env to te STDIN, if has check(), prints declare -x + env[i]
	//ECHO_BUILTIN -> Print args, if has -n without \n
	//PWD_BUILTIN -> Prints $PWD
/*
	이건 뭐
*/
void	pwd_builtin(void )
{
	char	path[1024];

	printf("%s\n", getcwd(path, 1024));
	exit(0);
}

/*
	1. echo 다음 옵션이 -n이면 플래그를 올린다.
	2. 그냥 echo -n로 끝나버리면, \n만 하고 끝낸다.
	3. 그 다음 쭉 읽으면서 다음에 나오는걸 쭉 출력한다. 그 다음에 덩어리가 또 있으면 스페이스 넣어주고
		다음이 없으면 \n이긴 한데, 첫번째 조건은 위에 i플래그랑 완전히 같은데?
*/
void	echo_builtin(char **command_split)
{
	int	i;

	if (ft_strcmp(command_split[1], "-n"))
		i = 1;
	else
		i = 0;
	if (!command_split[i + 1])
	{
		if (i == 0)
			printf("\n");
		exit(0);
	}
	while (command_split[++i])
	{
		printf("%s", command_split[i]);
		if (command_split[i + 1])
			printf(" ");
		else if (!ft_strcmp(command_split[1], "-n") && !command_split[i + 1])
			printf("\n");
	}
	exit(0);
}

/*
	1. export
	export에선 check 1, env에선 check 0이 들어간다. 옵션 들어가면 안된다.
	아무튼 env 다 나오는데, declare -x가 붙어서 나와야 한다.
	2. env
	check 0이 들어간다. 옵션이 들어가면 터져야하고, declare 없는거 빼곤 같다.
*/
void	env_bu(char **env, int nbr_command, int check)
{
	int	i;

	if (nbr_command > 1 && check == 0) 
		status_error("No such file or directory", 127);
	else
	{
		i = -1;
		while (env[++i])
		{
			if (check == 1)
				printf("declare -x ");
			printf("%s\n", env[i]);
		}
	}
	exit(0);
}

/*
	exit 5 입력하면 작동해야 한다. 숫자 아니면 터져야하고, 2개 이상 들어가면 안된다.
	그리고 잘 들어갔다면 exit도 출력해줘야한다.
*/
void	exit_builtin_child(char **command_split, int nbr_command)
{
	int	i;

	i = -1;
	if (nbr_command > 1)
	{
		while (command_split[0][++i])
		{
			if (!ft_isdigit(command_split[0][i]))
				status_error("Numeric argument required", 255);
		}
	}
	if (nbr_command > 2)
		status_error("Too many arguments", 1);
	else
	{
		if (nbr_command == 2)
			exit(ft_atoi(command_split[0]));
		exit(0);
	}
}

/*
	child에 빌트인 명령어가 들어온다면
	1. export -> 여기 옵션 들어간건 구현할 필요 없다.
	2. env -> echo 말고 옵션 들어간거 구현할 필요 없다.
	3. unset -> unset과 cd는 왜 그냥 꺼지지? 
	4. cd
	5. pwd
	6. echo
	7. exit 그냥 exit만 있으면 끝낸다. 근데 옵션..? 이 붙어있으면? 구현할건 아닌데 어쨌든 숫자도 들어가나
*/
void	check_builtins_child(t_shell **sh, int id)
{
	if (ft_strcmp((*sh)->my_pro->child[id].command_split[0], "export"))
	{
		if ((*sh)->my_pro->child[id].nbr_command == 1)
			env_bu((*sh)->my_env->env, (*sh)->my_pro->child[id].nbr_command, 1);
		else
			exit(0);
	}
	else if (ft_strcmp((*sh)->my_pro->child[id].command_split[0], "env"))
		env_bu((*sh)->my_env->env, (*sh)->my_pro->child[id].nbr_command, 0);
	else if (ft_strcmp((*sh)->my_pro->child[id].command_split[0], "unset"))
		exit(0);
	else if (ft_strcmp((*sh)->my_pro->child[id].command_split[0], "cd"))
		exit(0);
	else if (ft_strcmp((*sh)->my_pro->child[id].command_split[0], "pwd"))
		pwd_builtin();
	else if (ft_strcmp((*sh)->my_pro->child[id].command_split[0], "echo"))
		echo_builtin((*sh)->my_pro->child[id].command_split);
	else if (ft_strcmp((*sh)->my_pro->child[id].command_split[0], "exit"))
	{
		if ((*sh)->my_pro->nbr_process > 1)
			exit_builtin_child(&(*sh)->my_pro->child[id].command_split[1],
				(*sh)->my_pro->child[id].nbr_command);
		else
			exit (1);
	}
}
