
#include "minishell.h"
#include "minishell_louis.h"

void	ft_display_lexer(t_data data)
{
	t_token	*curr_token;

	while (data.tokens)
	{
		curr_token = (t_token *)data.tokens->content;
		dprintf(STDERR_FILENO, "New	");
		dprintf(STDERR_FILENO, "str : %s, ", curr_token->string);
		dprintf(STDERR_FILENO, "          ");
		dprintf(STDERR_FILENO, "type : %d, ", curr_token->type);
		dprintf(STDERR_FILENO, "expand : %d, ", curr_token->expand);
		dprintf(STDERR_FILENO, "join : %d, ", curr_token->join_with_next);
		dprintf(STDERR_FILENO, "in quote : %d, ", curr_token->quote);
		dprintf(STDERR_FILENO, "empty : %d\n", curr_token->empty_node);
		data.tokens = data.tokens->next;
	}
}
