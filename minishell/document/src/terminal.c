#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "../include/minishell.h"

//CREATE_TERMINAL -> while (1) loop. 
	//SIG_HANDLER -> Sets signals ^D / ^C / ^\ (mom or ch with global g_mother)
	//GET_LINE -> Prints the prompt, addhistory
	//(processes.c)
//FREE_AND_INIT -> Frees data for the new input line
	//FT_FREE -> Make sure if exist data and free

void	ft_free(void *to_free)
{
	if (to_free)
	{
		free(to_free);
		to_free = NULL;
	}
}

void	free_and_init(t_shell *shell)
{
	int	a;
	int	i;

	a = -1;
	while (++a < shell->my_pro->nbr_process)
	{
		ft_free(shell->my_pro->fd[a]);
		i = -1;
		while (++i < shell->my_pro->child[a].nbr_infile)
			ft_free(shell->my_pro->child[a].infile_t[i].file_name);
		i = -1;
		while (++i < shell->my_pro->child[a].nbr_outfile)
			ft_free(shell->my_pro->child[a].outfile_t[i].file_name);
		ft_free(shell->my_pro->child[a].outfile_t);
		ft_free(shell->my_pro->child[a].infile_t);
		ft_free(shell->my_pro->child[a].command_group);
		free_double(shell->my_pro->child[a].command_split, 2);
	}
	ft_free(shell->my_pro->pid);
	ft_free(shell->my_pro->fd[a]);
	ft_free(shell->my_pro->fd);
	ft_free(shell->my_pro->child);
	free_double(shell->my_pro->orders, 2);
	ft_memset(shell->my_pro, 0, sizeof(t_pro));
}

/*
	get_line
	1. 프롬프트를 만들어준다.
	2. readline으로 입력받은 것을 shell->line으로 넣는다.
	shell->line = readline("minishell >") 
*/
char	*get_line(t_shell *shell) //프롬프트를 만들어준다
{
	/*
		이전 명령을 삭제한다.
	*/
	if (shell->line && shell->line[0] != '\0')
	{
		ft_free(shell->line);
		shell->line = NULL;
	}

	/*
		readline으로 무언가를 읽는데 성공하면, addhistory로 저장한다.
	*/
	shell->line = readline("Pink Peanuts > ");
	if (shell->line && shell->line[0] != '\0')
		add_history(shell->line);

	/*
		만약 들어온 명령어가 history -c 라면, 모두 지워야한다.
		strncmp는 같으면 0 나온다.
	*/
	if (shell->line && !ft_strncmp(shell->line, "history -c",
			ft_strlen("history -c")))
		rl_clear_history();

	//리턴
	return (shell->line); 
}


void	sig_handler(int signum)
{
	/* 
		g_mother == 1 정상입력, SIGINT
		개행 후, readline으로 읽은 것을 다 지운다. 그 다음 디스플레이? 이건 뭐지?
		(참고)원본 bash는 컨트롤 d로 끝날때 exit앞에 개행이 뜨지 않는다. 근데 이건 뜨는데... 이게 여기서 처리되는건가?
	*/
	if (signum == SIGINT && g_mother == 1)
	{
		printf("\n"); 
		rl_on_new_line();
		rl_replace_line("", 0); //line buffer에 있는 내용을 지운다.
		rl_redisplay(); //버퍼에 있는걸로 디스플레이에 업데이트? 더 정확히 봐야겠다.
	}

	if (signum == SIGINT && g_mother == 4)
	{
		printf("\n");
		rl_on_new_line();
	}
	if (signum == SIGQUIT && g_mother == 4)
		write(1, "Quit : 3\n", 9); //명령어 실행 ex: cat하고,
		//아마 대기상태면(추정), g_mother가 4로 하나보다. 아무튼, 그 중간에 컨트롤 d하면 이게 나온다.
}

int	create_terminal(t_shell *shell)
{
/*
	rl_catch_signal = 0 일때,시그널로 종료했을때, 이상한게 안뜨게 해준다. 더 자세한 내용은 알아봐야한다.
	rl_catch_signal = 1 일때, readline은 SIGINT 등의 시그널들을 자기가 정의한걸로 사용하게 된다.
	g_mother = 1일때 -> 터미널 입력 상태(추정), sig_handler을 통해 종료 시그널에 반응하는 방법을 정해준다. 
*/
	g_mother = 1;
	shell->line = NULL;
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);


	while (1)
	{
		/*
			get_line
			1. 프롬프트를 만들어준다. (minishell > )
			2. readline으로 입력받은 것을 shell->line으로 넣는다.
		*/
		shell->line = get_line(shell); 

		/*
			shell->line이 없다 = 종료신호가 들어온 것. 정상입력은 아무것도 입력하지 않아도, 개행이라도 들어오게 된다.
		*/
		if (!shell->line)
		{
			printf("exit\n");
			exit(0);
		}

		/*
			readline으로 잘 읽었다면, g_mother = 4로 설정한다. 자식프로세스로 들어간다면 1로 바뀐다.
			input으로 들어가서 
		*/
		else if (shell->line[0] != '\0')
		{
			g_mother = 4; //g_mother = 4
			input(shell);
			ft_free(shell->line);
			shell->line = NULL;
			g_mother = 1; //그냥 처음으로 초기화하는거네.(추정)
		}
	}
	return (0);
}
