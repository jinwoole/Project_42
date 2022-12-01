/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:04:43 by zcanales          #+#    #+#             */
/*   Updated: 2022/08/15 11:51:58 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//FILTER_UNSET -> Builtin unset. If the name of the var is invalid error
//child_info.c -- get_child_info()
	//*COUNT_PEAKS -> Counts brackets or doubles to malloc array of in/outfiles
	//*CLEAN_COMMANDS ->Dollar and quotes of in/outfiles and command
		//(quote.c / dollar.c)
	//*COUNT_NBR_COMMANDS -> Counts command and args to malloc the array

//////////UNSET////////////

/*
	unset이랍시고 들어온 친구가 뭔가 상태가 이상하면 1을 리턴해서 바깥의 !filter_unset 조건문을 작동하지 않게 한다.
*/
int	filter_unset(char *var)
{
	int	a;

	a = -1;
	while (var[++a])
	{
		if (!ft_isalnum(var[a]) && var[a] != '_')
		{
			printf("Pink peanuts: %s not a valid identifier\n", var);
			return (1);
		}
	}
	return (0);
}

/////////CLEAN COMMANDS//////////

/*
	Counts command and args to malloc the array
	그냥 딱봐도 child의 command_split이 몇 개 있는지 세주는거다.
*/
void	count_nbr_commands(t_ch *child)
{
	int	a;

	a = -1;
	child->nbr_command = 0;
	if (!child->command_split)
		return ;
	while (child->command_split[++a])
		child->nbr_command++;
}

/*
	CLEAN_COMMANDS 환경변수를 치환해 넣어준다.
*/
void	clean_commands(t_shell *shell, t_ch *child)
{
	int	a;

	/*
		child->command_split이 잘 들어갔다면, fill_quote_dollar로 환경변수를 모두 치환한다.
	*/
	if (child->command_split)
		child->command_split = fill_quote_dollar(child->command_split,
				shell, child->nbr_command, 2);
	/*
		child->infile, outfile -> 리디렉션 뒤의 filename의 환경변수를 치환한다.
	*/
	a = -1;
	while (++a < child->nbr_infile) 
	{
		child->infile_t[a].file_name_clean
			= fill_quote_dollar(&child->infile_t[a].file_name,
				shell, child->nbr_infile, 1);
		child->infile_t[a].file_name
			= convert_array_to_string(child->infile_t[a].file_name_clean); 
			//그 다음 Clean을 가져다가 file_name[a]에 그대로 넣어주네?
			//그냥 1차원 배열로 도로 바꿀라고
	}
	a = -1;
	while (++a < child->nbr_outfile) //outfile의 과정은 같다.
	{
		child->outfile_t[a].file_name_clean
			= fill_quote_dollar(&child->outfile_t[a].file_name,
				shell, child->nbr_outfile, 1);
		child->outfile_t[a].file_name
			= convert_array_to_string(child->outfile_t[a].file_name_clean);
	}
}

/*
	COUNT_PEAKS -> c를 기준으로 몇개나 잘리나 보고, t_peak을 초기화한다.

	1. ft_split2 함수를 통해 c를 기준으로 몇개나 잘렸는지, nbr_file에 세준다. 그리고 free
	2. 받아온 포인터 file_t에 c를 기준으로 잘랐을때 잘 들어가게 동적할당한다.
	3. file type는 1이다 = 초기화한다. file type은 리디렉션 <의 개수
*/
void	count_peaks(int *nbr_file, char c, t_peak **file_t, char *order)
{
	int		i;
	char	**file;

	file = ft_split_2(order, c, nbr_file);
	i = -1;
	free_double(file, 2);
	(*file_t) = (t_peak *)ft_calloc(sizeof(t_peak), (*nbr_file + 1));
	if (!(*file_t))
		status_error(strerror(errno), errno);
	i = -1;
	while (++i < *nbr_file)
		(*file_t)[i].type = 1;
}
