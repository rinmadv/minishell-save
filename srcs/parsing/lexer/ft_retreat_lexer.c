#include "minishell.h"
#include "minishell_louis.h"

void	ft_change_join_bool(t_list *prev, t_list *curr)
{
	t_token	*curr_token;
	t_token	*prev_token;

	curr_token = (t_token *)curr->content;
	prev_token = (t_token *)prev->content;
	if (prev_token->join_with_next && !curr_token->join_with_next)
		prev_token->join_with_next = false;
}


int	ft_retreat_lexer(t_info *info)
{
	t_list	*list;
	t_token	*current_token;
	t_list	*prev;

	list = info->tokens;
	prev = NULL;
	while (list)
	{
		current_token = (t_token *)list->content;
		if (current_token->type == type_word)
		{
			if (ft_split_quotes(list) != FUNCTION_SUCCESS)
				return (MEMORY_ERROR_NB); // attention, mal clean
			if (current_token->quote && ft_remove_quotes(list, current_token->string[0]) == LINE_IS_EMPTY)
			{
				if (prev)
					ft_change_join_bool(prev, list);
				current_token->empty_node = true;
			}
		}
		prev = list;
		list = list->next;
	}
	return (FUNCTION_SUCCESS);
}
