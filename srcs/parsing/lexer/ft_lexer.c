
#include "minishell.h"
#include "minishell_louis.h"

int	ft_simple_expand_from_start(t_token *current_token, t_envlist *env)
{
	t_envlist	*tmp_start_env = env;
	int			dollar_loc;

	dollar_loc = ft_strchr_int(current_token->string, '$');
	while (env && ft_strncmp(&current_token->string[dollar_loc + 1], (const char*)env->key, ft_strlen(env->key)))
		env = env->next;
	//free(current_token->string); a remettre mais ya un invalide free
	if (!env)
		current_token->empty_node = true;
	else
	{
		current_token->string = ft_strdup(env->val); //ca c'est si on est entre double quotes, si cest pas le cas, faudra splitter et faire plusieurs autres maillons
		if (!current_token->string)
			return (MEMORY_ERROR_NB);
	}
	env = tmp_start_env;
	return (FUNCTION_SUCCESS);
}

int	 ft_detatch_expand(t_list *list, int i, t_envlist *env)
{
	t_token	*current_token;

	current_token = (t_token *)list->content;
	if (i == 0)
	{
		i++;
		while (current_token->string[i] && (!ft_is_space(current_token->string[i]) && !ft_is_dollar(current_token->string[i])))
			i++;
		if (current_token->string[i])//detacher ce qui vient apres
		{
			if (ft_insert_next_node(i, list) != FUNCTION_SUCCESS)
				return (MEMORY_ERROR_NB);
		}
		ft_simple_expand_from_start(current_token, env);
	}
	return (FUNCTION_SUCCESS);
}

int	ft_expand(t_info *info, t_envlist *env)
{
	t_list	*list;
	t_token	*current_token;
	int		dollar_loc;

	list = info->tokens;
	dollar_loc = 0;
	while (list)
	{
		current_token = (t_token *)list->content;
		if (current_token->type == type_word && (current_token->quote != simple_q))
		{
			//printf("ouiii\n");
			dollar_loc = ft_strchr_int(current_token->string, '$');
			if (dollar_loc >= 0)
			{
				ft_detatch_expand(list, dollar_loc, env);
			}
		}
		list = list->next;
	}
	return (FUNCTION_SUCCESS);
}


/******************************************************************/

int	ft_init_token(t_token *new_token, const char *input, int *i)
{
	new_token->string = NULL;
	new_token->string = get_token_val(input, i);
	if (!new_token->string)
		return (MEMORY_ERROR_NB); //free des trucs aussi
	new_token->type = get_token_type(new_token->string);
	new_token->expand = false;
	new_token->join_with_next = false;
	new_token->quote = no_q;
	new_token->empty_node = false;
	return (FUNCTION_SUCCESS);
}

int	ft_lexer(const char *input, t_info *info, t_envlist *envp)
{
	int		i;
	t_list	*new_node;
	t_token	*new_token;

	i = 0;
	while (input[i])
	{
		if (!ft_check_empty_line(input, i))
			break;
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (MEMORY_ERROR_NB);
		if (ft_init_token(new_token, input, &i) != FUNCTION_SUCCESS)
			return (MEMORY_ERROR_NB); //penser a bien free
		new_node = ft_lstnew((void *)new_token);
		if(!new_node)
			return (MEMORY_ERROR_NB);
		ft_lstadd_back(&info->tokens, new_node);
	}
	if (ft_retreat_lexer(info) != FUNCTION_SUCCESS) 
		return (MEMORY_ERROR_NB);
	ft_expand(info, envp);
	return (FUNCTION_SUCCESS);
}
