
#include "minishell.h"
#include "minishell_louis.h"


void	close_pipes(t_data *data, t_pipe *pipes)
{
	if (data->nb_command > 1)
	{
		close(pipes->tube[0][0]);
		close(pipes->tube[0][1]);
	}
	close(pipes->tube[1][1]);
	close(pipes->tube[1][0]);
	free(pipes);
}

void	close_list_args(t_cmd **cmd, int len_list,
	int stdin_save, int stdout_save)
{
	int	i;

	i = 0;
	while (i < len_list)
	{
		if (cmd[i]->input != pipe_in_)
		{
			if (cmd[i]->fd_in == 0)
				dup2(stdin_save, 0);
		}
		if (cmd[i]->output != pipe_out_)
		{
			if (cmd[i]->fd_out == 1)
				dup2(stdout_save, 1);
		}
		i++;
	}
}
