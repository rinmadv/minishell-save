
#include "minishell.h"
#include "minishell_louis.h"

int	prompt(t_data *data)
{
	const char	*input;

	while (1)
	{
		handle_signals_prompt();
		input = readline(YELLOW"aristoshell$ "NC);
		//printf("Exec val : %d\n", data->exec_val);
		if (input && input[0] != 0)
		{
			add_history(input);
			if (parsing(data, input))
			{
				free((void *)input);
				clear_history();
				return (MEMORY_ERROR_NB);
			}
			if(cross_array_list(data) == EXIT)
			 	return (ft_clean_t_data(data), EXIT);
			ft_reinit_data(data);
		}
		else if (!input)
			exit(0);
	}
	clear_history(); // mauvais endroit I guess
	return(FUNCTION_SUCCESS);
}
