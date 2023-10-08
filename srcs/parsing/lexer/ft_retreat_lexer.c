#include "minishell.h"
#include "minishell_louis.h"

int	ft_retreat_lexer(t_info *info)
{
	t_list	*list;
	t_token	*current_token;

	list = info->tokens;
	while (list)
	{
		current_token = (t_token *)list->content;
		if (current_token->type == type_word)
		{
			if (ft_split_quotes(list) != FUNCTION_SUCCESS)
				return (MEMORY_ERROR_NB); // attention, mal clean
			if (current_token->quote && ft_remove_quotes(list, current_token->string[0]) == LINE_IS_EMPTY)
				current_token->empty_node = true;
		}
		list = list->next;
	}
	return (FUNCTION_SUCCESS);
}
