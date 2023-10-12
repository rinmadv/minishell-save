
#include "minishell.h"
#include "minishell_louis.h"

// penser a initialiser les currents

bool	ft_check_empty_tokens_list(t_list *list)
{
	t_token	*curr_tok;

	while (list)
	{
		curr_tok = (t_token *)list->content;
		if (curr_tok->empty_node != true)
			return (false);
		list = list->next;
	}
	return (true);
}

int	ft_fill_tab_cmd(t_data *data, t_list *list)
{
	t_token	*curr_token;

	data->current_cmd = 0;
	curr_token = (t_token *)list->content;
	while (data->current_cmd < data->nb_command)
	{
		if (ft_init_cmd(data, data->current_cmd) != FUNCTION_SUCCESS)
			return (MEMORY_ERROR_NB); //et free des trucs
		if (ft_fill_cmd(data->cmd[data->current_cmd], list) != FUNCTION_SUCCESS)
			return (MEMORY_ERROR_NB);
		data->current_cmd++;
		while (curr_token->type != type_pipe)
		{
			list = list->next;
			if (!list)
				return (FUNCTION_SUCCESS);
			curr_token = (t_token *)list->content;
		}	
	}
	return (FUNCTION_SUCCESS);
}


int	ft_parser(t_info *info, t_data *data)
{
	printf("data(ft_parser 1) -> %p\n", data);
	data->nb_command = 0;
	printf("data(ft_parser 2) -> %p\n", data);
	if (ft_check_empty_tokens_list(info->tokens))
	{
		ft_reinit_data(data);
		return (printf("LINE IS EMPTY\n"), LINE_IS_EMPTY);
	}
	ft_count_cmd(info->tokens, data);
	//printf("nb cmd : %d\n", data->nb_command);
	if (ft_init_tab_cmd(data) !=  FUNCTION_SUCCESS)
		return (MEMORY_ERROR_NB);
	ft_fill_tab_cmd(data, info->tokens);
	ft_display_tab_cmd(data);
	ft_reinit_data(data);
	return (0);
}
