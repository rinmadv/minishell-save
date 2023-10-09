
#include "minishell.h"
#include "minishell_louis.h"

// penser a initialiser les currents

// void	check_redirect_in(t_cmd	*cmd, t_tokens **tokens, int *curr_cmd, int *curr_word)
// {
// 	if (word[0])
// }

// void	fill_cmd(t_cmd	*cmd, t_tokens **tokens, int *curr_cmd, int *curr_word)
// {
// 	while (tokens[*curr_word]->type > type_pipe)
// 	{
// 		check_redirect_in(cmd, tokens, curr_cmd, curr_word);
// 	}	
// }



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
	printf("nb cmd : %d\n", data->nb_command);
}

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


int	ft_fill_tab_cmd(t_data *data, t_info *info)
{
	int	i;

	i = 0;//utilisr current cmd
	while (i < data->nb_command)
	{
		ft_init_cmd(data, i);
		if (i == 0) //plus besoin, on va juste en mettre 1
		{
			if (ft_fill_cmd(data->cmd[i], data->cmd[i]->fd_out, info, true) != FUNCTION_SUCCESS)//vraiment a changer car degueu
				return (MEMORY_ERROR_NB);
		}
		else
		{
			if (ft_fill_cmd(data->cmd[i], data->cmd[i-1]->fd_out, info, false)!= FUNCTION_SUCCESS)
				return (MEMORY_ERROR_NB);
		}
		i++;
	}
	return (FUNCTION_SUCCESS);
}


int	ft_parser(t_info *info, t_data *data)
{
	if (ft_check_empty_tokens_list(info->tokens))
	{
		ft_reinit_data(data);
		return (printf("LINE IS EMPTY\n"), LINE_IS_EMPTY);
	}
	ft_count_cmd(info->tokens, data);
	if (ft_init_tab_cmd(data) !=  FUNCTION_SUCCESS)
		return (MEMORY_ERROR_NB);
	ft_fill_tab_cmd(data, info);
	// //ft_display_tab_cmd(*data);
	ft_reinit_data(data);
	return (0);
}
