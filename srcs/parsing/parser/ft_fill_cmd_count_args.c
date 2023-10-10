
#include "minishell.h"
#include "minishell_louis.h"

int	ft_fill_cmd_count_args(t_list *list)
{
	int nb_agrs;
	t_token	*curr_token;

	nb_agrs = 0;
	curr_token = (t_token*)list->content;
	while (curr_token->type != type_pipe)
	{
		if (curr_token->type == type_word && !curr_token->redir_file)
			nb_agrs++;
		list = list->next;
		if (!list)
			return (nb_agrs);
		curr_token = list->content;
	}
	return (nb_agrs);
}
