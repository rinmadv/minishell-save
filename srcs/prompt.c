
#include "minishell.h"
#include "minishell_louis.h"

int	prompt(t_data *data)
{
	const char	*input;
	int			function_return;

	while (1)
	{
		handle_signals_prompt();
		input = readline(YELLOW"aristoshell$ "NC);
		if (input && input[0] != 0)
		{
			add_history(input);
			function_return = parsing(data, input);
			free((void *)input);
			input = NULL;
			if (function_return)
				return (clear_history(), MEMORY_ERROR_NB);
			if(cross_array_list(data) == EXIT)
			 	return (clear_history(), ft_clean_t_data(data), EXIT);
			ft_reinit_data(data);
		}
		else if (!input)
			exit(0);
	}
	clear_history();
	return (FUNCTION_SUCCESS);
}
