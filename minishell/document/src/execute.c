/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:06:18 by eperaita          #+#    #+#             */
/*   Updated: 2022/02/17 15:46:23 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>
#include <signal.h>

//CLOSE PIPES -> Closing all pipes, after duplicating fd
//IS_REDIRECTED -> if it has in/out open the file in the fd
	//here_doc.c
	//RE_IN_OUT ->
//RE_PIPE -> changes the STDIN and STDOUT for the execvue
//EXE -> executes the command and args

/*
	열어준 모든 프로세스를 반복해서 닫는다.
	id는 id+1만큼 받아서 쓰니 넘프로세스+1 까지 가야하는것 같고 ,j 는 0하고 1만 본다.	
*/
void	close_pipes(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (i < shell->my_pro->nbr_process + 1)
	{
		j = 0;
		while (j < 2)
		{
			close(shell->my_pro->fd[i][j]);
			j++;
		}
		i++;
	}
}

/*
	is_redirected 리디렉션 처리 <, > << >> heredic 상황을 처리한다.
	1. nbr_infile -> 리디렉션 횟수 만큼 반복한다.
		1. 처음 시작하면 here_doc은 지워야지
		2. 2번타입 -> << 이면, heredoc을 받아야 한다.
		3. child의 리디렉션 횟수 - 1 이 i가 아니면 지워주네?
	2. re_in_out -> 리디렉션 종류별로 처리한다. fd에 적합하게 열어준다.
*/
void	is_redirected(t_pro *pro, int id)
{
	int	i;

	i = -1;
	while (++i < pro->child[id].nbr_infile)
	{
//		if (i == 0) 잘 되는것 같은데 이 앞에서 지우니 지워도 될 것 가다.
//			unlink("here_doc.txt");
		if (pro->child[id].infile_t[i].type == 2)
		{
			here_doc(pro, i, id);
			if (i != (pro->child[id].nbr_infile - 1))  
				unlink("here_doc.txt");
		//이 -1 한게 i와 같지 않으면????? 모르겠다
		//리디렉션 뒤에, cat << ls >> test.txt / cat<< ls는 작동하고, 넣고  모르겠다..????
		}
		else
			re_in_out(pro, 0, i, id);
	}
	i = -1;
	while (++i < pro->child[id].nbr_outfile)
		re_in_out(pro, 1, i, id);
}

void	re_in_out(t_pro *pro, int in_out, int index, int id)
{
	/*
		0번일때는 heredoc이 아닌 infile이 들어왔음을 의미한다. 진짜 파일 이름을 받아다가 열어준다. infile이 [0]
	*/
	if (in_out == 0)
	{
		printf("flare\n");
		pro->fd[id][0] = open(pro->child[id].infile_t[index].file_name, 
				O_RDONLY);
		if (pro->fd[id][0] < 0)
			status_error(strerror(errno), errno);
	}
	/*
		outfile인 경우엔? 그러니까 > 일때도 들어오고 >> 일때도 들어온다. 나머지는 아니다.
		1. > type일때, fd[id + 1][1]에다가 파일을 연다. 다만 > 니깐, 덮어씌워야 한다(TRUNC -> 파일 있으면 길이 0으로 해서 연다)
		2. >> 일때, 덮어씌워야 하니 O_APPEND 모드로 열어야 한다.
		0644는 퍼미션 설정이다. write하고 read권한이었나? 줘야한다.
		3. 물론 실패하면 터져야한다.
	*/
	if (in_out == 1)
	{
		if (pro->child[id].outfile_t[index].type == 1) 
			pro->fd[id + 1][1] = open(pro->child[id].outfile_t[index].file_name,
					O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (pro->child[id].outfile_t[index].type == 2)
			pro->fd[id + 1][1] = open(pro->child[id].outfile_t[index].file_name,
					O_RDWR | O_CREAT | O_APPEND, 0644);
		if (pro->fd[id + 1][1] < 0)
			status_error(strerror(errno), errno);
	}
}

void	re_pipe(t_shell *shell, int id) //쉘, child id바든다.
{
	/*
		0번 차일드 = 처음.이 아니거나
		아니면, 처음이지만, 리디렉션이 있을때(추정) -> infile이니 < 겠지? 
		infile, heredoc일 경우, fd[id][0]에서 처리된다.
		파이프는 없는데, infile이 없으면 == Heredoc이다!
		아래 fd[id][0] 0은 heredoc에 처리해준다.
		heredoc자체는 standardin으로 넣어주면 된다. 그 다음 마지막 것들은 다 넣어주는것들이다.
		그리고 Infile일떼도 [0]으로 읽으니, standard input으로 넣어준거다!
	*/
	if (id != 0 || (id == 0 && shell->my_pro->child[id].nbr_infile)) 
		dup2(shell->my_pro->fd[id][0], 0); //re_in_out에서 설정한걸, fd[0]-> stdin으로 들어오게 만든다.
	if (id != shell->my_pro->nbr_process - 1)  //마지막 파이프가 아니면,
		dup2(shell->my_pro->fd[id + 1][1], 1);
	else if (id == shell->my_pro->nbr_process - 1
		&& shell->my_pro->child[id].nbr_outfile) //마지막 파이프면서, 막판에 아웃파일이 있으면...?
		dup2(shell->my_pro->fd[id + 1][1], 1);

//성민이가 합쳤다. 근데 어떻게 설명한다? 마지막이 outfile이거나, 아니면 (파이프 단위로)마지막에 아닐 경우의 아웃파일일 경우, stdout으로 넣어야 한다.
//echo "hello" >> text.txt했을때, "Hello"가 뜨면 안되는데, else if를 안쓰니 나온다.
	close_pipes(shell);
}

/*

*/
void	exe_command(t_shell *shell, int id)
{
	int		i;
	char	*temp_access;

	/*
		아무 명령도 안들어올수가 있나? 널일 경우에도 파이프 개수로 하기때문에
		만들어주긴 하는데, 이게 어떻게 들어올 수 있지? 없어도 될 것 같다. 없어도 잘 작동한다.
	*/
	if (!shell->my_pro->child[id].command_split[0]) 
		exit(0);
	i = -1;
	while (shell->my_env->paths[++i])
	{
		/*
			1. path[i]랑 실행할 파일이랑 합친다.
			2. 그 파일을 열 수 있는지 확인한다. 근데 허용함수가 아니네 open활용해서 ft_access만들어야한다
			3. 열 수 있다면, 그리고 child[id]가 마지막 프로세스가 아니라면, child[id]에 run 신호를 보내준다.
		*/
		temp_access = ft_strjoin(shell->my_env->paths[i],
				shell->my_pro->child[id].command_split[0]); 
		if (!access(temp_access, X_OK))
		{
			if (shell->my_pro->child[id].id_child != shell->my_pro->nbr_process - 1)
				kill(shell->my_pro->pid[shell->my_pro->child[id].id_child], SIGCONT); 
				//SIGCONT는 stop상태를 run으로 만들어준다.
			execve(ft_strjoin(shell->my_env->paths[i],
					shell->my_pro->child[id].command_split[0]), 
				shell->my_pro->child[id].command_split,
				shell->my_env->env);
				//그리고경로랑 커맨드 븉여서 실행시킨다. 이거 실행되면, 미니쉘은 그 순간 다 없어진다.
		}
		free(temp_access);
	}
	printf_error(shell->my_pro->child[id].command_split[0], 2, shell);
	exit(127);
}
