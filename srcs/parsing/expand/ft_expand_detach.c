
#include "minishell.h"
#include "minishell_louis.h"

int	ft_detatch_expand_first(int *i, t_list *list)
{
	t_token	*current_token;
	char	*truncate;

	current_token = (t_token *)list->content;
	*i += 1;
	while (current_token->string[*i] && (!ft_is_space(current_token->string[*i]) && !ft_is_dollar(current_token->string[*i])))
		*i += 1;
	if (current_token->string[*i])//detacher ce qui vient apres
	{
		if (ft_insert_next_node(*i, list) != FUNCTION_SUCCESS)
			return (MEMORY_ERROR_NB);
		current_token->join_with_next = true;
	}
	current_token->expand = true;
	truncate = ft_strtrim(current_token->string, "$");
	if (!truncate)
		return (MEMORY_ERROR_NB);
	free(current_token->string);
	current_token->string = ft_substr(truncate, 0, *i-1);
	free(truncate);
	if (!current_token->string)
		return (MEMORY_ERROR_NB);
	return (FUNCTION_SUCCESS);
}

int	ft_detatch_expand_not_first(int *i, t_list *list)
{
	t_token	*current_token;
	char	*truncate;

	current_token = (t_token *)list->content;
	if (ft_insert_next_node(*i, list) != FUNCTION_SUCCESS)
		return (MEMORY_ERROR_NB);
	if (current_token->join_with_next)
	{
		t_token *next = (t_token *)list->next->content;
		next->join_with_next = true;
	}
	current_token->join_with_next = true; //important de le garder apres
	truncate = ft_substr(current_token->string, 0, *i);
	if (!truncate)
		return (MEMORY_ERROR_NB);
	free(current_token->string);
	current_token->string = truncate;
	return (FUNCTION_SUCCESS);
}

int	 ft_detatch_expand(t_list *list, int i)
{
	if (i == 0)
		return (ft_detatch_expand_first(&i, list));
	else
		return (ft_detatch_expand_not_first(&i, list));
	return (FUNCTION_SUCCESS);
}
