
#include "minishell.h"
#include "minishell_louis.h"

int	ft_fill_cmd(t_cmd *cmd, t_list *list)
{
	int	nb_args;

	if (ft_fill_cmd_redirs_files(cmd, list))
		return (MEMORY_ERROR_NB);
	nb_args = ft_fill_cmd_count_args(list);
	if (ft_fill_cmd_init_tab_args(nb_args, cmd) == MEMORY_ERROR_NB)
		return (MEMORY_ERROR_NB);
	if (ft_fill_cmd_fill_tab_args(cmd, list, nb_args))
		return (MEMORY_ERROR_NB);
	return (FUNCTION_SUCCESS);
}
