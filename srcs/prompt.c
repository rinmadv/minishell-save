
#include "minishell.h"
#include "minishell_louis.h"

bool	check_exit(const char *input)
{
	if (!input || ft_strncmp(input, "exit", ft_strlen(input) + 1) == 0)// a changer, car ca doit faire partie de lexec
	{
		// ft_dprintf(STDIN_FILENO, "exit\n"); mettre ailleurs
		// clear_history(); //peut etre qu'il faudra le mettre dans le return de prompt car je sais pas si ca va marcher la
		return (true);
	}
	return (false);
}

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
			 	return (EXIT);
			ft_reinit_data(data);
		}
		else if (!input)
			exit(0);
	}
	clear_history(); // mauvais endroit I guess
	return(FUNCTION_SUCCESS);
}
