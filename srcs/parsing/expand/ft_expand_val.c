
#include "minishell.h"
#include "minishell_louis.h"

int	ft_expand_val(t_list *list, t_envlist *env)
{
	t_envlist	*tmp_start_env = env;
	t_token	*current_token;

	current_token = (t_token *)list->content;
	while (env && ft_strncmp(current_token->string, (const char*)env->key, ft_strlen(env->key)))
		env = env->next;
	free(current_token->string); //maybe invalide free
	if (!env)
	{
		current_token->empty_node = true;
		current_token->string = NULL;
	}
	else
	{
		current_token->string = ft_strdup(env->val); //ca c'est si on est entre double quotes, si cest pas le cas, faudra splitter et faire plusieurs autres maillons
		if (!current_token->string)
			return (MEMORY_ERROR_NB);
	}
	env = tmp_start_env;
	return (FUNCTION_SUCCESS);
}
