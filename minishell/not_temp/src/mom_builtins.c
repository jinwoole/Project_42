/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mom_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:35:10 by eperaita          #+#    #+#             */
/*   Updated: 2022/08/14 13:59:14 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//CHECK_BUILTINS_MOTHER -> Handle his builtns
	//CHANGE_ENV -> Export and unset
		//GET_REAL_VARS -> Filter syntax of vars
			//FIND_EQUAL_CHAR -> Finds equal
		//(export_unset.c)
//EXIT_BUILTIN -> Filter args and exit

/*
	exit_builtin(nbr_com은 각 child의 nbr_command
	1. 일단 exit을 했으면 exit을 출력해야 한다.
	2. 일단, exit만 딱 들어온게 아니면(nbr_com > 1) 뭐가 들어왔나 확인해 숫자가 아니면 에러
	3. exit + 숫자 말고 또 뭐가 뒤에 들어왔으면, 오류. status_builtin을 1로 해준다... 왜?
	4. 아무튼 nbr_com은 1 아니면 2여야 한다. 2일땐 exit code가 나와야하니 이렇게 해준다.
	5. 그냥 exit이면 exit 0이지
*/
static void	exit_builtin(char **command_split,
		int nbr_com, t_shell *shell, int id)
{
	int	i;

	i = -1;
	printf("exit\n");
	shell->my_pro->child[id].mom_builtin = 1; //이걸 다시 1로 해주는데 뭐지?
	if (nbr_com > 1)
	{
		while (command_split[0][++i])
		{
			if (!ft_isdigit(command_split[0][i])) 
				status_error("Numeric argument required", 127);//참고로 여긴 255가 맞다
		}
	}
	if (nbr_com > 2)
	{
		printf_error("exit", 3, shell);
		shell->status_builtin = 1;
	}
	else if (nbr_com == 2)
		exit(ft_atoi(command_split[0]));
	else
		exit(0);
}

/*
	export 할때, 잘 들어갔는지 오류처리하고, ENV=SOMETHING 이걸 var_real에 저장한다.
*/
static void	find_equal_char(char **s, t_shell *shell)
{
	int	i;
	int	a;

	shell->my_env->nbr_var = -1;
	a = -1;
	while (s[++a])
	{
		i = 0;
		/*
			=까지 반복문으로 지나친다. export 다음 알파벳, 숫자, _를 제외한 어떤 것들이 나오면 오류
		*/
		while (s[a][i] && s[a][i] != '=' )
		{
			if (!ft_isalnum(s[a][i]) && s[a][i] != '_')
			{
				printf_error(s[a], 1, shell);//
				break ;
			}
			i++;
		}
		/*
			export = 할때 =이 있으면 shell의 my_env의 index에 가서 그걸 바꿔버린다.
			그냥 export lee=1 하면, var_real[0]에 lee=1 들어간다.
		*/
		if (s[a][i] && s[a][i] == '=')
			shell->my_env->var_real[++shell->my_env->nbr_var]
				= ft_substr(s[a], 0, ft_strlen(s[a]));
	}
	shell->my_env->var_real[++shell->my_env->nbr_var] = NULL;
	//아무튼 이렇게 var_real을 완성시킨다.
}

/*
	get_real_vars(nbr_command_split -> cd면 3, 그 외엔 child->nbr_command)
	env->var_real을 만든다. exoprt MAIL=sob222 뭐 이런거 한다면, 추가되는건 따로 관리하면 좋다
	replace 2 들어오면 cd일때
*/
void	get_real_vars(t_shell *shell, char **command_split,
		int nbr_command_split, int replace)
{
	int	a;

	shell->my_env->var_real = (char **)ft_calloc(sizeof(char *), nbr_command_split);
	if (!shell->my_env->var_real)
		status_error(strerror(errno), errno);
	/*
		unset이 아닐때(replace != 0) -> find_equal_char -> var_real에 export한거 저장
	*/
	if (replace != 0)
		find_equal_char(command_split, shell);
	/*
		unset일때, command_split(한 파이프에 들어간 명령 조각)을 쭉 보면서
		일단 var_real에 통째로 집어넣어 준다.
		통째로 env에 넣어준다. an=3 뭐 이렇게 했을때, 만약 아무것도 없으면 완전히 새로 추가한다? 후속조치를 봐야겠다.
	*/
	else
	{
		a = -1;
		while (command_split[++a])
			shell->my_env->var_real[a] = ft_strdup(command_split[a]);
		shell->my_env->var_real[a] = NULL;
	}
}

/*
	change_env
	export와 unset명령어에서 사용한다. cd하는 와중에도 있다 => replace ==  2
	cd일땐 			get_real_vars(shell, ar, 3, replace)
	export, unset	get_real_vars(shell, var, child_nbr_command, replace)
*/
static void	change_env(t_shell **shell, char **var,
		int id, int replace)
{
	if (replace == 2)
		get_real_vars(*shell, var, 3, replace);
	else
		get_real_vars(*shell, var, (*shell)->my_pro->child[id].nbr_command,
			replace);
	(*shell)->my_pro->child[id].mom_builtin = 1; //무슨 뜻일까? 빌트인 함수라는 뜻일까?
	/*
		위에서 만든 real_vars를 적절한 예외처리를 거쳐 링크드 리스트화시킨다. 왜냐하면 뭘 추가해야하니깐
	*/
	create_lists(*shell, replace);
	/*
		근데 왜 프로세스가 1개일때만 작동해야하지? 만약에 파이프 뒤에 뭐가 있다고 하면 그건 어떻게 되나? 작동하면 안되나?
		replace_env -> export 일때, 기존 env를 스캔하다가 같은게 있으면 바꾸고 아님 추가한다. unset이면 그냥 env를 모두 지나친다.
		convert_list_array -> list_env를 가져다가 **env에 다시 넣는다.
		get_new_paths -> 만약 export나 unset등으로 바뀌었다면 path 등을 다시 가져와야한다.
	*/
	if ((*shell)->my_pro->nbr_process == 1)
	{
		replace_env((*shell), replace);
		(*shell)->my_env->env = convert_list_array(shell); 
		get_new_paths((*shell)->my_env->env, *shell); 
		ft_freelist(&(*shell)->my_env->list_var_real);
	}
	free_double((*shell)->my_env->var_real, 2);
}

/*
	check_builtins_mother(id는 child[id])
	get_child_info에서 들어옴.
	파이프에 들어온 명령들이 빌트인인지 확인한다.
*/
void	check_builtins_mother(t_shell **shell, int id)
{
	char	**new_vars;

	/*
		명령이 export라면? change_env를 해줘야 한다. 어쨌든 export는 환경변수를 추가해준다.
		그런데, export만 있으면 또 안되니 1보다 커야한다.
		참고로 change_env의 flag 1, 0은 그냥 export냐 unset이냐, 2는 cd일 경우이다.
	*/
	if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "export")
		&& (*shell)->my_pro->child[id].nbr_command > 1)
		change_env(shell, &(*shell)->my_pro->child[id].command_split[1], id, 1);
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "unset"))
		change_env(shell, &(*shell)->my_pro->child[id].command_split[1], id, 0);
	/*
		cd일 경우, 현재 위치를 바꿔야 한다. OLDPATH 등 이 친구도 환경변수를 변경해야 하니 아래 change_env로 마무리한다.
	*/
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "cd"))
	{
		(*shell)->my_pro->child[id].mom_builtin = 1;
		new_vars = (char **)ft_calloc(sizeof(char *), 3);
		if (!new_vars)
			status_error(strerror(errno), errno);
		/*
			위에 calloc 3인 이유는 cd, 경로, 널 들어가야 하니깐
			new_vars에 cd_builtin으로 집어넣는다. cd로 바뀐 현재경로와 이전경로 환경변수를 집어넣고 쉘 환경변수를 바꾼다.
		*/
		new_vars = cd_builtin((*shell)->my_env->env,
				&(*shell)->my_pro->child[id].command_split[1],
				new_vars, (*shell)); 
		if (!new_vars)
			return ;
		change_env(shell, new_vars, id, 2);
		free_double(new_vars, 2);
	}
	/*
		exit이고, 파이프 또 없어야 작동한다. exit | echo 5 하면 exit만 작동한다.
	*/
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "exit")
		&& (*shell)->my_pro->nbr_process == 1)
		exit_builtin(&(*shell)->my_pro->child[id].command_split[1],
			(*shell)->my_pro->child[id].nbr_command, *shell, id);
}
