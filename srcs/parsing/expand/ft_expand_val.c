
#include "minishell.h"
#include "minishell_louis.h"

int	ft_insert_expand_splitted(t_list *list, char *new_word, bool join_next)
{
	t_token *new_token;
	t_list	*new;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (MEMORY_ERROR_NB);
	new_token->string = new_word;
	new_token->type = type_word;
	new_token->expand = false;
	new_token->join_with_next = join_next; //pb ici, attention pour le dernier
	new_token->quote = false;
	new_token->empty_node = false;
	new_token->redir_file = false;
	new = ft_lstnew((void *)new_token);
	if (!new)
		return (MEMORY_ERROR_NB);
	new->next = list->next;
	list->next = new;
	return (FUNCTION_SUCCESS);
}


int	ft_expand_val_split(t_list *list, char *env_val)
{
	char	**splited;
	t_token	*current_token;

	current_token = list->content;
	splited = NULL;
	int i = 0;
	splited = ft_split(env_val, ' ');
	if (!splited)
		return (MEMORY_ERROR_NB);
	current_token->empty_node = true;
	while (splited && splited[i])
	{
		if (splited[i + 1] || current_token->join_with_next)
			ft_insert_expand_splitted(list, splited[i], true);
		else
			ft_insert_expand_splitted(list, splited[i], false);
		i++;
		list = list->next;
	}
	return (FUNCTION_SUCCESS);
}

int	ft_expand_val(t_list *list, t_envlist *env)
{
	t_envlist	*tmp_start_env = env;
	t_token	*current_token;

	current_token = (t_token *)list->content;
	while (env && ft_strncmp(current_token->string, (const char*)env->key, (ft_strlen(current_token->string) + 1)))
		env = env->next;
	free(current_token->string); //maybe invalide free
	if (!env)
	{
		current_token->empty_node = true;
		current_token->string = NULL;
	}
	else if (current_token->quote == double_q)
	{
		current_token->string = ft_strdup(env->val);
		if (!current_token->string)
			return (MEMORY_ERROR_NB);
	}
	else
	{
		current_token->string = NULL; //a delete apres, juste pour pas derreurs
		ft_expand_val_split(list, env->val); //add verif
	}
	env = tmp_start_env;
	return (FUNCTION_SUCCESS);
}
