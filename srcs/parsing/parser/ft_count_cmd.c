
#include "minishell.h"
#include "minishell_louis.h"

void	ft_count_cmd(t_list *list, t_data *data)
{
	t_token	*curr_tok;

	data->nb_command = 1;
	while (list)
	{
		curr_tok = (t_token *)list->content;
		if (curr_tok->type == type_pipe)
			data->nb_command += 1 ;
		list = list->next;
	}
}
