/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:59:12 by zcanales          #+#    #+#             */
/*   Updated: 2022/08/14 11:47:31 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//CONVERT_LIST_ARRAY
//REPLACE_ENV -> Adds or deletes (replace 1/0) $VARS to the env
	//REPLACE_REPEATED -> if its repeated replace
		//REPLACE_FIRST -> replace head of linked list
//CREATE_LIST -> Gets the env and vars in a linked list

/*
	change_env의 함수.
	unset혹은 Export할때, 추가된 환경변수들은 var_real으로 들어간다. 
	그리고 사용하기 위해, 둘다 링크드 리스트로 만들어서 원본env와 우리가 커스텀한 환경변수들을 합쳐서 사용하게 된다
*/
void	create_lists(t_shell *shell, int replace)
{
	int	i;

	/*
		최종적으로 사용하는건 list_var_real. 이걸 만들기 위해 먼저 main에서 받아온 env를 그대로 넣어준다.
	*/
	i = -1;
	while (shell->my_pro->nbr_process == 1 && shell->my_env->env[++i])
	{
		ft_lstadd_back(&shell->my_env->list_env,
			ft_lstnew(shell->my_env->env[i])); 
	}
	/*
		export의 경우, var_real을 읽으면서 맨 앞이 =가 아니면서 알파벳이거나 _라면
			그런데 또 replace가 0(unset)이 아니던가 그런데, 0이면서 filter_unset(이상한글자 확인), 파이프로 잘린게 없으면
			var_real[i]는 통과되어 list_var_real에 들어간다. 아니면 오류지 뭐. unset 202020 입력해보면 같다.
	*/
	i = -1;
	while (shell->my_env->var_real[++i])
	{
		if (shell->my_env->var_real[i][0] != '='
				&& (ft_isalpha(shell->my_env->var_real[i][0])
					|| shell->my_env->var_real[i][0] == '_'))
		{
			if ((replace != 0 || (replace == 0
					&& !filter_unset(shell->my_env->var_real[i]))) && shell->my_pro->nbr_process == 1)
				ft_lstadd_back(&shell->my_env->list_var_real, ft_lstnew(shell->my_env->var_real[i]));
		}
		else
			printf_error(shell->my_env->var_real[i], 1, shell);
	}
}

int	replace_first(t_list **head_env, t_list *temp_var, int replace)
//first로 Head를 바꾸는 이유가 뭐지?
//env와 Tmp가 있다고 하면,repeated에선 그 다음부터 비교한다. back이 env고, temp는 그 다음.
//temp var은 또 따로 있다.
//왜 두번째부터 보냐? 현재부터 보면, 그 다음을 temp의 첫번째부터 비교한다. 왜냐하면 다음이 있으면, temp다음을 넣어주고 그 head다음을 지워주면 된다
//이러면 마지막에 꼬인다. 그런 경우를 대비해서, 첫번째 예외를 처리해준다.
//처음껀 예외적으로 처리 -> 
{
	t_list	*temp;
	t_list	*to_free;

	temp = *head_env;
	to_free = *head_env;
	if (ft_strcmp_len((char *)temp->content, //원본 환경변수 안에 이미 똑같은 친구가 있으면 여기로 들어온다. 아니면 리턴0된다.
			(char *)temp_var->content))
	{
		if (replace != 0) //그리고 0이 아니면(unset이 아니면)
		{
			temp = temp->next; //다음 노드로 가서
			(*head_env) = ft_lstnew((char *)temp_var->content); //env안에 컨텐츠를 넣어버린다
			(*head_env)->next = temp;
		}
		else
			(*head_env) = temp->next;
		free(to_free);
		return (1);
	}
	return (0);
}

int	replace_repeated(t_list **head_env, t_list *temp_var, int replace) //head_env는 list_env, temp_var은 export나unset으로 갖고노는구역
{
	t_list	*temp_back;
	t_list	*temp_env;

	if (replace_first(head_env, temp_var, replace)) //이거 했을때->
		return (0);
	temp_back = *head_env;
	temp_env = temp_back->next;
	while (temp_env)
	{
		if (ft_strcmp_len((char *)temp_env->content, (char *)temp_var->content))
		{
			if (replace != 0) //export가 들어왔을때의 결과. 기존의 것을 지우고, export로 들어온 것으로 대체한 것(추정)
			{
				temp_back->next = ft_lstnew((char *)temp_var->content);
				temp_back->next->next = temp_env->next;
			}
			else //unset으로 우리가 만든 것을 지운다. unset의 결과(추정)
				temp_back->next = temp_env->next;
			free(temp_env);
			return (0);
		}
		temp_back = temp_back->next;
		temp_env = temp_back->next;
	}
	return (1);
}	

//원본은 보관해야 한다. 왜냐하면 Child끼리 enviroment가 충돌하면 안된다.
//replace repeated -> 처음 본 함수인가?



/*
	이제 기존의 env 리스트와 var_real리스트가 준비되었으니, 합친다. replace가 0==unset이면 작동하지 않고 그냥 앞으로 쭉 간다
	replace_repeated ->  env와 var 사이에 같은게 없다 = 새로운 것이니 그냥 넣는다.
*/
void	replace_env(t_shell *shell, int replace)
{
	t_list	*temp_var;

	temp_var = shell->my_env->list_var_real;
	while (temp_var)
	{
		if (replace_repeated(&shell->my_env->list_env, temp_var, replace) && replace != 0)
			ft_lstadd_back(&shell->my_env->list_env, ft_lstnew((char *)temp_var->content));
		temp_var = temp_var->next;
	}
}

/*
	list_env를 가져다가
	2차원 배열인 temp_env에 가져다 넣는다
*/
char	**convert_list_array(t_shell **shell)
{
	char	**temp_env;
	t_list	*temp;
	int		i;

	i = -1;
	temp = (*shell)->my_env->list_env;
	(*shell)->my_env->nbr_env = ft_lstsize(temp);
	temp_env = (char **)malloc(sizeof(char *)
			* ((*shell)->my_env->nbr_env + 1));
	if (!temp_env)
		status_error(strerror(errno), errno);
	while (temp)
	{
		temp_env[++i] = ft_strdup((char *)temp->content);
		temp = temp->next;
	}
	temp_env[(*shell)->my_env->nbr_env] = NULL;
	ft_freelist(&(*shell)->my_env->list_env);
	free_double((*shell)->my_env->env, 2);
	(*shell)->my_env->env = NULL;
	return (temp_env);
}
