
#include "minishell.h"
#include "minishell_louis.h"

int	ft_fill_cmd_fill_tab_args(t_cmd *cmd, t_list *list, int nb_args)
{
	int	i;
	t_token	*curr_token;

	i = 0;
	curr_token = (t_token*)list->content;
	while (i < nb_args)
	{
		if (curr_token->type == type_word && !curr_token->redir_file)
		{
			cmd->cmd_args[i] = ft_strdup(curr_token->string);
			if (!cmd->cmd_args[i])
				return (MEMORY_ERROR_NB); // GRRRRR
			i++;
			info->current_token++;
		}
		list = list->next;
		if (!list)
			(break;);
		curr_token = list->content;
	}
	cmd->cmd_args[i] = malloc(sizeof(char) * 1);	
	if (!cmd->cmd_args[i])
		return (MEMORY_ERROR_NB); // GRRRRR
	cmd->cmd_args[i] = NULL;
	return (FUNCTION_SUCCESS);
}
