/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:30:38 by eperaita          #+#    #+#             */
/*   Updated: 2022/08/17 14:36:37 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>

//INPUT -> Checks input errors and goes to:
	//ALLOC PROCESSES -> Allocate pids(childs), fd(pipes) 
		//(child_info.c)
	//CREATE PROCESSES -> Forks each child, gets pids and sends t_ch(cleaned)
		//CHILD PROCESS -> (execute.c)
		//MOTHER -> Waits for childs. Each return gets status and unlocks next.
//(terminal.c - free_and_init() -> frees data)

void	child_process(t_ch *child, t_shell *shell)
{
	/*
		1. 초기화
			heredoc 지우고, g_sig_md = 0, rl_catch_signals = 1
		rl_catch_signals -> readline 실행중에 시그널을 표시해줄지(기본 1)

		- rl_catch_signal =1 일때, readline은 SIGINT 등의 시그널들을 자기가 정의한걸로 사용하게 된다.
		자식프로세스를 끄기위해 sigint(원래는 안꺼진다) sigquit를 보낼텐데, 
		이제 그건 우리가 핸들러를 통해서 하는게 아니라, 내장된걸로 처리하겠다!라는 선언.
	*/
	unlink("here_doc.txt");
	g_sig_md = 0;
	rl_catch_signals = 1;
	/*
		1. is_redirected 리디렉션 5종 처리
		2. re_pipe 열린 파일디스크립터를 stdin, stdout에 연결해준다.
		이 아래 child->command_split이 왜 있어야 하는지 모르겠다. command_split 건드리는 부분이 있긴 한가?
		3. check_builitins_child -> 차일드에 들어간게 빌트인 명령인지 확인한다.
		4. ./ 이건 파일실행이다. path를 실행파일 있는 절대경로로 바꾸고, command_split[0]에 파일이름 들어간다.
	*/
	is_redirected(shell->my_pro, child->id_child);
	re_pipe(shell, child->id_child);
	if (!child->command_split)
		exit(0);
	check_builtins_child(&shell, child->id_child);
	if (child->command_split[0] && (child->command_split[0][0] == '.'
		|| child->command_split[0][0] == '/'))
		child->command_split[0] = get_exe_path(shell, child->command_split[0]);
	g_sig_md = 0;
	exe_command(shell, child->id_child);
}

/*
	Waits for childs. Each return gets status and unlocks next.
	shell->status는 자식 프로세스에서 보내온 신호를 받는다. $?가 처리하는 그건가보다
*/
void	mother_process(t_shell *shell)
{
	int	i;
	int	status;
	int	pid;

	i = -1;
	while (++i < shell->my_pro->nbr_process)
	{
		/*
			waitpid(pid, status, option)
			-1 이면 임의의 자식 프로세스의 시그널을 기다린다.
		*/
		pid = waitpid(-1, &status, 0);
		/*
			WEXITSTATUS(status) -> 임의의 자식 프로세스가 보낸 exit 신호를 받아줄 수 있음
		*/
		if (pid == shell->my_pro->pid[shell->my_pro->nbr_process - 1])
				shell->status = WEXITSTATUS(status);
		/*
			그리고 조건은 위와 같은데, 거기다가 빌트인 함수기까지 하다면(추정) 그냥 statis_builitin
		*/
		if (pid == shell->my_pro->pid[shell->my_pro->nbr_process - 1]
			&& shell->my_pro->child[i].mom_builtin)
			shell->status = shell->status_builtin;
		/*
			근데, i가 마지막 프로세서가 아니라면 sigcont 신호를 보내서 어쨌든 그 다음을 재개시키네
		*/
		if (i != shell->my_pro->nbr_process - 1)
			kill(shell->my_pro->pid[i + 1], SIGCONT);
	}
	rl_catch_signals = 0;
}

/*
	CREATE PROCESS -> 각각의 자식 프로세스를 포크하고, pids를 받아서 구조체에 넣는다.
	exit_builtin을 마지막으로, 이제 프로세스 할당을 시작한다.
*/
void	create_processes(t_shell *shell)
{
	int	id;

	/*
		id를 반복문 겸 인덱스로 돌린다.
		pid의 마지막부터 포크한다. 터지면 에러내보내면 되고,
		pid != 0 -> 부모프로세스라면, 해당 자식프로세스를 향해 SIGSTOP명령을 보낸다.
		자식프로세스라면,
			g_sig_md = 0으로 설정한다. (추정)그냥 초기화같고, 지워도 잘 작동한다.
			child의 id정보를 넣어준다.
			child_process로 자식 프로세스가 일을 시작한다.
	*/
	id = shell->my_pro->nbr_process;
	while (id--)
	{
		shell->my_pro->pid[id] = fork(); 
		if (shell->my_pro->pid[id] < 0)
			status_error(strerror(errno), errno);
		if (shell->my_pro->pid[id] != 0)
			kill(shell->my_pro->pid[id], SIGSTOP); //kill명령을 보낸다? 자식프로세스에서 readline에서 커스텀되는데,

		else
		{	
			g_sig_md = 0;
			shell->my_pro->child[id].id_child = id;
			child_process(&shell->my_pro->child[id], shell);
		}
	}
	/*
		자식 프로세스는 죽는다. 이 아래를 받을 수 있는것은 부모프로세스. pid[0]에 stop을 start시킨다.
		그리고 파이프를 다 닫는다.
		그리고 부모의 일을 한다.ㄴ
	*/
	kill(shell->my_pro->pid[0], SIGCONT);
	close_pipes(shell);
	mother_process(shell);
}


/*
	shell구조체에 필요한 정보를 넣는다.
	특히, Allocate pids(childs), fd(pipes)를 설정한다.
*/
int	init_processes(t_shell *shell)
{
	int	i;
	int	npipes;

	shell->my_pro->orders = ft_split_2(shell->line, 
			'|', &shell->my_pro->nbr_process); 
	if (is_empty_pipe(shell->my_pro->orders))
		return (1);
	printf("%d\n", shell->my_pro->nbr_process);
	npipes = (shell->my_pro->nbr_process + 1);
	i = -1;
	shell->my_pro->fd = (int **)malloc(npipes * sizeof(int *));
	while (++i < npipes)
	{
		shell->my_pro->fd[i] = (int *)malloc(2 * sizeof(int));
		if (!shell->my_pro->fd[i])
			status_error(strerror(errno), errno);
		if (pipe(shell->my_pro->fd[i]) < 0)
			status_error(strerror(errno), errno);
	}
	i = 0;
	shell->my_pro->pid = (int *)malloc(shell->my_pro->nbr_process
			* sizeof (int));
	if (shell->my_pro->pid < 0)
		status_error(strerror(errno), errno);
	get_child_info(shell);
	return (0);
}


/*
	input
		input들에 에러가 있는지 확인한다.(is *)
	init_processes
		child프로세스들에 필요한 정보들과 파이프를 위한 공간을 할당한다.
	create_processes
		각각의 child프로세스를 포크하고 ch구조체를 보낸다.
*/
int	input(t_shell *shell)
{
	unlink("here_doc.txt");

	if (is_line_error(shell->line))
	{
		shell->status = 258;
		return (1);
	}
	if (init_processes(shell))
	{
		shell->status = 258;
		free_double(shell->my_pro->orders, 2);
		return (1);
	}
	create_processes(shell);
	free_and_init(shell);
	return (0);
}
