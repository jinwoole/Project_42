/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:38:25 by eperaita          #+#    #+#             */
/*   Updated: 2022/08/16 21:16:17 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Libft/libft.h"
# include <unistd.h>
# include <termios.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>


/*
	g_mother
	signal 상태 -> 무한입력 상태인지, 터미널 정상 입력 상태인지에 따라 시그널 받을 방법을 정해준다.
	자식프로세스 : 1, 부모프로세스 : 4 (추정) terminal.c, input()->create_process에서 분기가 나뉘게 된다.
	0은 또 뭐야. child_process 에서 exe_command하기 직전에 바뀐다.
	근데 자식 프로세스 시작하면 0으로 초기화하는데?
*/
int	g_mother;     // g_sig_md

typedef struct s_piquito // s_file
{
	int		type;  				// redir_type		리디렉션이 < 하나만 있으면 1, 두개<< 있으면 2이다.
	char	*file_name; 		// file_name		order에서 dequote를 한 리디렉션 파일 이름
	char	**file_name_clean;	// file_name_tmp	리디렉션 파일 이름을 환경변수를 치환해서 넣은 것
	
	//문 : 왜 command_split은 그대로 넣었으면서 file_name_clean은 따로 만들었나?
	//답 : file_name_clean은 fill_quote_dollar쓰기위해 위해 2차원 배열로 한 것. 
	//어차피 array[0]에만 들어가고 file_name은 본래 문자열이다.

}	t_peak; // t_file

typedef struct s_ch // s_child
{
	t_peak		*infile_t;			// t_file infile		infile, outfile : 리디렉션을 통해 들어오는 원본 명령,파일 이름.
	t_peak		*outfile_t; 		// t_file outfile		얘는 >
	char		*command_group;		// redir_cmd	각 파이프에서 리디렉션으로 잘랐을때, 맨 앞에 있을 명령
	char		**command_split;	// sep_order	각 파이프에 들어가있는 명령 echo, -n, "Hello"
	int			mom_builtin;		// builtin_flag	bulitin함수다 플래그(추정)
	int			id_child;			// idx			내가 몇 index child라고 알려준다. 파이프기준으로 몇번째인가? create_process
	int			nbr_command;		// cmd_nbr		command split해서 된 것의 개수 = 각 파이프에 들어가있는 명령의 인자 개수. echo -n "hello"는 3개 word count
	int			nbr_infile; 		// infile_nbr	한 파이프에 redirection으로 읽을 파일의 개수(추정)
	int			nbr_outfile;		// outfine_nbr
	int			index_in;			// index_in
	int			index_out;			// index_out
}	t_ch; // t_child

typedef struct s_pro // s_pros
{
	int		nbr_process;	// nbr_procs		alloc_process 의 split2에서 nbr-process를 센다 = 파이프로 잘린 = 프로세스의 개수
	int		**fd;			// fd				alloc_process에서 파이프 입출구가 미리 설정되었다.
	char	**orders;		// orders			파이프 기준으로 잘린 명령들
	pid_t	*pid;			// pid_t pid		processes/alloc_process에서 할당. 어디서 사용하는지 보고 기록해놓자
	t_ch	*child;			// t_child child	각 파이프 기준으로	실행되어야 할 자식프로세스들의 정보
}	t_pro; // t_pros

typedef struct s_env
{
	char	**env; 			// env			main에서 받아온 env를 그대로 넣어준다. -> change_env에서, export나 unset으로 가공된 친구들을 다시 넣어준다.
	char	**paths;		// paths
	char	**var_real;		// new_env		export, unset등으로 가공한 것들
	char	*home;			// home
	int		nbr_env; 		// nbr_var		mom_builtin에서 var_real의 index로 쓰인다
	int		nbr_var; 		// nbr_var		mom_builtin에서 var_real의 index로 쓰인다
	t_list	*list_var_real; // list_new_env	create_lists 함수에서 var_real과 env를 이 리스트에 집어넣는다.
	t_list	*list_env;		// list_env		Create_list함수의 시작에서 env를 리스트로 넣는다.
}	t_env;

typedef struct s_shell
{
	int				check;			// flag				(없앰)이거 그냥 fill_quote_dollar 끝내는 일회용 플래그다.
	int				status_builtin;	// builtin_status	이게 뭐지? get_child_info에 출현, exit_builtin의 오류상황에 1로 설정
	int				status;			// cur_status		return하게 될 error code일 것이다(추정) expand_dollar에서, $? 들어왔을때 이 값을 리턴한다. 그리고 mother_process에서 사용한다.
	char			*line;			// line				create_terminal, readline으로 읽어온 내용을 넣는다. 동 함수에서 free된다.
	t_env			*my_env;		// t_envs cp_envs
	t_pro			*my_pro;		// t_envs cp_pros
}	t_shell;

/*	INIT	*/
void	init(t_shell **shell, char **env);
void	get_environment(t_env *my_env, char **env);

/* TERMINAL	*/
int		create_terminal(t_shell *shell);
void	free_and_init(t_shell *shell);
void	ft_free(void *to_free);
void	sig_handler(int signum);

/*PROCESSES*/
int		input(t_shell *shell);
int		alloc_processes(t_shell *shell);
void	create_processes(t_shell *shell);
void	child_process(t_ch *child, t_shell *shell);
void	mother_process(t_shell *shell);

/*CHILD_INFO*/
void	chop_files(t_ch *ch, char c, int *i, char *order);
char	*chop_command(t_ch *ch, int *i, char *order);
void	classify_order(t_ch *ch, char *order);
void	get_child_info(t_shell *shell);

/*CLEAN_COMMAND*/
void	clean_commands(t_shell *shell, t_ch *child);
void	count_nbr_commands(t_ch *child);
void	count_peaks(int *nbr_file, char c, t_peak **file_t, char *order);
int		filter_unset(char *var);

/*EXECUTE*/
void	close_pipes(t_shell *shell);
void	exe_command(t_shell *shell, int id);
void	re_in_out(t_pro *pro, int in_out, int index, int id);
void	re_pipe(t_shell *shell, int id);
void	is_redirected(t_pro *pro, int id);

/*UTILS*/
void	free_double(char **s, int check);
void	ft_freelist(t_list **head);
char	*convert_array_to_string(char **array);
char	*ft_substr_strjoin(char *to_sub, char *to_join, int start, int end);
int		ft_strcmp_len(char *env, char *var);

/*	QUOTE	*/
int		check_quotes(char *s, int *index);
void	decode_quotes(t_shell *shell, char **str, int *i, int *start);
char	**fill_quote_dollar(char **array, t_shell *shell,
			int nbr_array, int check);

/*	DOLLAR	*/
char	*expand_dollar(t_shell *shell, char *str, int *i);
int		replace_dollar(char **str, int start, int len, char *replace);
char	*fill_dollar(t_shell *shell, int *i, char *array);

/*  MOM_BUILTINS    */
void	get_real_vars(t_shell *shell, char **commnad_real,
			int nbr_commnad_real, int replace);
void	check_builtins_mother(t_shell **shell, int id);

/*PATH*/
void	get_new_paths(char **env, t_shell *shell);
char	*get_exe_path(t_shell *shell, char *command_split);
void	get_find(char **find, char *command);
char	*special_paths(char **env, char **command);

/*CD_BUILTIN*/
char	**cd_builtin(char **env, char **command_split,
			char **new_vars, t_shell *shell);

/*  EXPORT_UNSET    */
void	create_lists(t_shell *shell, int replace);
int		replace_first(t_list **head_env, t_list *temp_var, int replace);
int		replace_repeated(t_list **head_env, t_list *temp_var, int replace);
void	replace_env(t_shell *shell, int replace);
char	**convert_list_array(t_shell **shell);

/*  CHILD_BUILTINS    */
void	check_builtins_child(t_shell **shell, int id);

/* FT_SLIPT_2 */
char	**ft_split_2(char const *s, char c, int *nbr_array);

/*HERE_DOC*/
void	here_doc(t_pro *pro, int index, int id);

/*ERRORS */
int		check_error( char *line);
int		check_error_pipe(char **orders);
void	status_error(char *str, int err);

/*ERRORS_2 */
int		check_two_pipe(char *line);
int		check_empty_pipe(char **orders);
int		check_null_pipe(char *line);
int		check_line_empty(char *line);
void	printf_error(char *s, int err, t_shell *shell);

/*READLINE*/
void	rl_replace_line(const char *str, int i);
void	rl_clear_history(void );

#endif
