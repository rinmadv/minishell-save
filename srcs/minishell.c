
#include "minishell.h"
#include "minishell_louis.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argv ;
	if (argc != 1)
		return (ft_error(WRONG_NB_ARG, NULL));
	if (!envp)
		return (ft_error(NO_ENV, NULL));
	data = NULL;
	data = ft_create_data(envp);
	if (!data)
		return (ft_error(MEMORY_ERROR_NB, NULL), MEMORY_ERROR_NB);
	if (prompt(data) == MEMORY_ERROR_NB)
		return (MEMORY_ERROR_NB); //add ce que je dois effacer
	if (data)
		ft_clean_t_data(data);
	return (0);
}
