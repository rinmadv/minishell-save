#include "minishell.h"
#include "minishell_louis.h"

int	ft_fill_cmd_redirs_pipe_in(t_cmd *cmd, t_data *data)
{
	t_files	*redirs;
	t_list	*new;

	printf("\tpipe in\n");
	if (data->current_cmd != 0)
	{
		printf("\t\tcréation d'un maillon\n");
		redirs = malloc(sizeof(t_files));
		if (!redirs)
			return (MEMORY_ERROR_NB);
		redirs->filename = NULL;
		redirs->filetype = pipe_in_;
		redirs->open = false;
		redirs->redirect = false;
		new = ft_lstnew((void *)redirs);
		if (!new)
			return (MEMORY_ERROR_NB);
		ft_lstadd_back(&cmd->list_files, new);
	}
	return (FUNCTION_SUCCESS);
}

int	ft_fill_cmd_redirs_pipe_out(t_cmd *cmd, t_data *data)
{
	t_files	*redirs;
	t_list	*new;

	printf("\tpipe out\n");
	if (data->current_cmd != data->nb_command - 1)
	{
		printf("\t\tcréation d'un maillon\n");
		redirs = malloc(sizeof(t_files));
		if (!redirs)
			return (MEMORY_ERROR_NB);
		redirs->filename = NULL;
		redirs->filetype = pipe_out_;
		redirs->open = false;
		redirs->redirect = false;
		new = ft_lstnew((void *)redirs);
		if (!new)
			return (MEMORY_ERROR_NB);
		ft_lstadd_back(&cmd->list_files, new);
	}
	return (FUNCTION_SUCCESS);
}

int	ft_fill_cmd_redirs_files(t_cmd *cmd, t_list *list)
{
	t_token	*curr_tok;//ici je gererais le ambigious
	t_files	*redir;
	t_list	*new;

	curr_tok = (t_token *)list->content;
	while (curr_tok->type != type_pipe)
	{
		while (list && curr_tok->type < type_from)
		{
			list = list->next;
			if (!list)
				return (FUNCTION_SUCCESS);
			curr_tok = (t_token *)list->content;
			if (curr_tok->type == type_pipe)
				return (FUNCTION_SUCCESS);
		}
		redir = malloc(sizeof(t_files));
		if (!redir)
			return (MEMORY_ERROR_NB);
		printf(RED"%d\n"NC, curr_tok->type);
		list = list->next;
		curr_tok = (t_token *)list->content;
		while (curr_tok->empty_node)
		{
			list = list->next;
			curr_tok = (t_token *)list->content;
		}
		curr_tok->redir_file = true;
		redir->filetype = append_;
		printf(YELLOW"%d\n"NC, redir->filetype);
		printf(YELLOW"%d\n"NC, append_);
		// redir->filename = strdup(curr_tok->string);
		// if (!redir->filename)
		// 	return (MEMORY_ERROR_NB);
		redir->filename = NULL;
		redir->open = false;
		redir->redirect = false;
		new = ft_lstnew((void *)curr_tok);
		if (!new)
			return (MEMORY_ERROR_NB);
		ft_lstadd_back(&cmd->list_files, new);
		printf(BLUE"%d\n"NC, redir->filetype);
	}
	return (FUNCTION_SUCCESS);
}

int	ft_fill_cmd_redirs(t_cmd *cmd, t_data *data, t_list *list)
{
	if (ft_fill_cmd_redirs_pipe_in(cmd, data)
		|| ft_fill_cmd_redirs_pipe_out(cmd, data)
		|| ft_fill_cmd_redirs_files(cmd, list))
		return (MEMORY_ERROR_NB);
	if (cmd->list_files)
		ft_print_redir_files(cmd->list_files);
	return (FUNCTION_SUCCESS);
}
