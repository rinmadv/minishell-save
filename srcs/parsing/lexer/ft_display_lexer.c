
#include "minishell.h"
#include "minishell_louis.h"

void	ft_display_lexer(t_info info)
{
	t_token	*curr_token;

	while(info.tokens)
	{
		curr_token = (t_token*)info.tokens->content;
		if (!curr_token->empty_node)
			dprintf(STDERR_FILENO, "str : %s, type : %d, expand : %d, join : %d, in quote : %d, empty : %d\n", curr_token->string, curr_token->type, curr_token->expand, curr_token->join_with_next, curr_token->quote, curr_token->empty_node);
		info.tokens = info.tokens->next;
	}
}
