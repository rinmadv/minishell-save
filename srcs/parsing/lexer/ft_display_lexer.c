
#include "minishell.h"
#include "minishell_louis.h"

void	ft_display_lexer(t_info info)
{
	t_token	*curr_token;

	while(info.tokens)
	{
		curr_token = (t_token*)info.tokens->content;
		dprintf(STDERR_FILENO, "str : %s, type : %d, expand : %d, join : %d, quote : %d\n", curr_token->string, curr_token->type, curr_token->expand, curr_token->join_with_next, curr_token->quote);
		info.tokens = info.tokens->next;
	}
}
