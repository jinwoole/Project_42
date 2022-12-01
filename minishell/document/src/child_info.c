/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:06:18 by eperaita          #+#    #+#             */
/*   Updated: 2022/08/17 23:20:39 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//GET_CHILD_INFO -> Mom cleans and chops orders to childs (clean_command.c)
	//CLASSIFY_ORDER -> Infiles, outfiles and command in each child structure. 
		//CHOP_COMMAND -> Joins each token in his array, (dequoted)
			//CHOP_FILES -> Dequote infiles and outfiles


/*
	chop_files -> 리디렉션 다음에 들어온 파일 정보를 infile과 outfile에 넣어준다.
*/
void	chop_files(t_ch *ch, char c, int *i, char *order)
{
	int		type;
	int		start;

	type = 1; //이거 초기화할때 애초에 1로 초기화해서 여기 또 할 필요는 없다. 그 전에 했던게 안바뀌었나?

	/*
		1. order[i]는 이미 < or > 다. 여기서 order[i+1]이 존재하고, 그리고 그게 c라면,
		타입은 2, << >>가 들어온 것. 그게 아니라면 그냥 < >
		2. 그 다음 있을 공백을 쭉 넘어간간 후 공백이 끝나고 뭐가 나온 부분을 start로 저장한다.
	*/
	if (order[++*i] && order[*i] == c) 
    {
        type = 2;
        *i += 1;
    }
	while (order[*i] && order[*i] == 32)
		*i += 1;
	start = *i;
	/*
		<<, < 그리고 공백을 모두 지난 후,
		order[i]가 있고, 공백이 아니고, <도 아니고, >도 아니라면 = 스페이스, >, < 가 아닌 모든 것을 파일이름으로 치고
		쭉 읽는다. 만약 쌍따옴표를 만나면, 만약 그 중간에 <같은거 있으면 개꼬이니 쭉 넘겨준다.
		그리고 만난게 쌍따옴표면 쭉 넘기고 "다음까지 간다.(check_quotes도 i를 이동시켜준다.)
	*/
	while (order[*i] && order[*i] != 32 && order[*i] != '<' && order[*i] != '>') 
	{
		check_quotes(order, i);
		*i = *i + 1;
	}
	/*
		c가 <를 만났으면, 왼쪽에 있는 친구에게 넣어줘야 한다. = infile로 들어온다.
		1. <일때 child[i]의 infile_t 안의 filename에 읽어들인 파일이름을 가져와서 넣어준다. malloc까지 해준다 하하
		2. >일때 outfile 안의 filename을 넣어준다.
	*/
	if (c == '<')
	{
		ch->infile_t[ch->index_in].file_name
			= ft_substr(order, start, *i - start);
		ch->infile_t[ch->index_in++].type = type;
	}
	else
	{
		ch->outfile_t[ch->index_out].file_name
			= ft_substr(order, start, *i - start);
		ch->outfile_t[ch->index_out++].type = type;
	}
}

/*
	CHOP_COMMAND -> Joins each token in his array, (dequoted)
	char *ch->command_group에 결과값을 return  -> 각 파이프의 맨 앞에 있는 명령(리디렉션 이전)
*/
char	*chop_command(t_ch *ch, int *i, char *order)
{
	int		start;
	char	*temp;
	char	*real_temp;

	real_temp = NULL; //이건 뭘까

	/*
		quote안에 명령이 있어도 작동해야한다 "echo" "catatatat" > "text" 이래도 작동해야한다.
		start는 0일수밖에 없다. 중요한건, 모든 부분을 지나서 리디렉션까지 가게 된다.
		그 후, substr을 잘라서 집어넣게 된다. substr속성을 나중에 확인하자.
	*/
	start = *i;
	while (order[*i] && order[*i] != '<' && order[*i] != '>')
	{
		check_quotes(order, i);
		*i += 1;
	} 
	temp = ft_substr(order, start, *i - start);
	/*
		없으면 집어넣고, 있으면 붙인다. 	echo cat > echo echo > t
	*/
	if (!ch->command_group)
		real_temp = ft_strdup(temp);
	else 
	{
		real_temp = ft_strjoin(ch->command_group, temp);
	}
	free(temp);
	return (real_temp);
}


/*
	classify_order: infile, outfile, command를 ch구조체에 각각 넣어준다.
*/
void	classify_order(t_ch *ch, char *order)//각각 child[i]와 order[i]를 인자로 받는다.
{
	int	i;

	i = 0;
	if (!order)
		return ;
	/*
		1. 공백을 쭉 넘긴다.
		2. order[i]가 있고, <를 만나면, chop_files <
		3. >를 만나면, chop_files >
		4. 리디렉션이 아니면, chop_command. 따지고 보면 공백 빼고 이게 첫번째겠네

		chop_files	 -> < 다음에 들어온 filename과 리디렉션 종류 정보를 넣어준다.
		chop_command -> 각 리디렉션 구간의 명령어들을 저장한다.
	*/
	while (order[i])
	{
		while (order[i] && order[i] == 32)
			i++;
		if (order[i] && order[i] == '<')
			chop_files(ch, '<', &i, order);
		else if (order[i] && order[i] == '>')
			chop_files(ch, '>', &i, order);
		else
			ch->command_group = chop_command(ch, &i, order);
	}
}

/*
	GET_CHILD_INFO -> 엄마가 명령을 손질하고 썰어서 애들에게 먹인다
	각 child는 파이프 기준으로 쪼갠 명령들을 실행한다.
*/
void	get_child_info(t_shell *shell)
{
	int	i;

	i = -1;
	shell->my_pro->child = (t_ch *)ft_calloc(sizeof(t_ch), //calloc 순서를 바꿔도 좋다.
			shell->my_pro->nbr_process);
	if (!shell->my_pro->child)
		status_error(strerror(errno), errno);

	while (++i < shell->my_pro->nbr_process)
	{
		/*
			1. count_peaks를 활용해 order[i]를 '<'로 잘린만큼 
			child[i]의 peak구조체를 각각 동적할당하고 초기화한다. nbr_infile도 넣어준다.
			2. 1번과 같은 과정인데 outfile > 을 해준다
			infile, outfile : 리디렉션으로 들어오는 파일 이름
		*/
		count_peaks(&shell->my_pro->child[i].nbr_infile, '<',
			&shell->my_pro->child[i].infile_t, shell->my_pro->orders[i]);
		count_peaks(&shell->my_pro->child[i].nbr_outfile, '>',
			&shell->my_pro->child[i].outfile_t, shell->my_pro->orders[i]);
		/*
			classify_order: infile, outfile, command를 ch구조체에 각각 넣어준다.
			ch->command_group : 각 파이프에서, 리디렉션으로 잘랐을때, 맨 앞에 있어야 하는 명령
		*/
		classify_order(&shell->my_pro->child[i], shell->my_pro->orders[i]);
		/*
			1. commad split -> 각 파이프에 들어가있는 명령들(echo, -n, hello) split2를 활용한다. ' ' 기준으로 끊은거지.
			2. split2의 글자수 세기 기능을 사용하지 않았다. 그 이유는 split는 스페이스 기준으로 count하기 때문에, 스페이스 많이 넣거나
			아니면 리디렉션 뒤의 스페이스까지 읽는다. 
			3. 그래서 진짜 명령어 개수를 세기위해 count_nbr_commands가 있다.
		*/
		shell->my_pro->child[i].command_split
			= ft_split_2(shell->my_pro->child[i].command_group, 
				' ', &shell->my_pro->child[i].nbr_command);
		count_nbr_commands(&shell->my_pro->child[i]);
		/*
			clean_commands -> 환경변수를 치환한다. 그런데 status builitin이 뭔질 모르겠다.
		*/
		clean_commands(shell, &shell->my_pro->child[i]);
		shell->status_builtin = 0;

		if (shell->my_pro->child[i].command_split) //집어넣은 split가지고 뭘 한다. split이 파이프 기준? 아마 차일드니 리디렉션 기준으로 나눈거겠지.
			check_builtins_mother(&shell, i);
	}	
}
