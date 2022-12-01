/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:08:01 by eperaita          #+#    #+#             */
/*   Updated: 2022/08/17 14:05:18 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>

//HERE_DOC -> Opens the STDIN and saves all in here_doc.txt
	//HERE_DOC_LOOP -> Reading from STDIN
	//NEW_FILENAME -> Sends filename as arg to child

static void	new_filename(t_pro *pro, int index, int id)
//cat << ls 하면, ls가 Finename인데, 근데 이렇게 하면 heredoc의 내용이 들어가야할 redirection이다 그러니 바꿔준다.
{
	free(pro->child[id].infile_t[index].file_name);
	pro->child[id].infile_t[index].file_name = ft_strdup("here_doc.txt");
}

/*
	here_doc_loop(fd -> heredoc연fd)
	stdin을 통해 읽어준다.
*/
static void	here_doc_loop(char *limit, int fd)
{
	char	*line;

	while (1)
	{
		/*
			1. readline으로 한줄씩 받을때 프롬포트 나오게 한다.
			2. 들어온게 limit -> 종료트리거면 종료한다.
			3. 만약 line으로 들어온게 아무것도 없으면 문제가 있는거다. 엔터만 하면 개행이라도 있지. readline 실패다.
			4. 아무튼 입력받은게 있으면 터미널로 뜨긴 해야하고, 그걸 fd로 직접 넣는다.
		*/
		line = readline(">");
		if (ft_strcmp(line, limit))
		{
			free(line);
			break ;
		}
		else if (!line)
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
		line = NULL;
	}
}

/*
	
*/
void	here_doc(t_pro *pro, int index, int id) //이거 수행하는건 자식프로세스인데?
{
	char	*limit;
	int		fd;

	g_sig_md = 3;
	signal(SIGINT, SIG_DFL); //시그널 변경을 취소하고, 기본으로 돌아간다.
	signal(SIGQUIT, SIG_DFL);
	/*
		g_sig_md 3 -> 입력모드

		<시그널 2개는 무슨 기능을 하나?>
		signal sigint를 모두 지우니, heredoc상황에서 컨트롤c해도 heredoc이 종료되지 않는다. 
		Signal sigquit을 모두 지우니, quit:3만 뜨고, 종료되지 않는다.
		밑의 시그널2개를 지우니... heredoc상황에선 종료는 된다. 근데, quit=3이나 뭐 그런 잡다한게 같이 뜬다.
		아무튼 여기 원본하고 다르다. ctrl+d는 엔터 뜨면 안되고, 컨트롤 역슬래쉬는 작동 안되는게 맞다.

		답:
		위는 진짜 끝내주는거. 디폴트 값으로 해서 끝내준다. ign으로 바꾸면 안끝내는걸러 봐선 그 기능이 맞다.
		근데 아래는, 동시에 호출되는데, 아래는 시그핸들러에 있는 행동->그 다음 나타내야 할 오류를 나타내준다.
	*/
	limit = ft_strdup(pro->child[id].infile_t[index].file_name);
	fd = open("here_doc.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	//옵션들 설명 : O_RDWR 읽기쓰기 다 가능, O_CREAT 없으면 만들어, O_APPEND 파일 쓰기할 경우, 파일 끝에서부터 쓴다
	if (fd < 0)
		status_error(strerror(errno), errno);
	/*
		limit은 heredoc 끝내는 키워드
		readline을 통해 무한반복 heredoc을 읽어주는 함수.
		다 하고 나서, limit free하고, fd도 닫는다.
	*/
	here_doc_loop(limit, fd); 
	new_filename(pro, index, id);
	free(limit); //limit -> heredoc종료키워드. 
	close(fd);

	/*
		완성된 후, fd[child id][0]에 넣었다. 0이 뭔지는 뒤에 나온다.
	*/
	pro->fd[pro->child[id].id_child][0] = open("here_doc.txt", O_RDONLY); 
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
