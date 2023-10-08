
#include "minishell.h"
#include "minishell_louis.h"

bool	ft_check_empty_line(const char *str, int i)
{
	while (str[i])
	{
		if (str[i] > 32)
			return (true);
		i++;
	}
	return (false);
}


int	parsing(t_data *data, const char *input)
{
	t_info	*info;
	int		function_return;
	
	info = NULL;
	if (!check_syntax(input)) // faudra juste appeler check quotes en fait
		return (SYNTAX_QUOTE_ERROR);
	else if (!ft_check_empty_line(input, 0))
		return (FUNCTION_SUCCESS);
	else
	{
		info = create_info(info);
		if (!info)
			return (ft_error(MEMORY_ERROR_NB)); //besoin d'effacer qq chose aussi
		function_return = ft_lexer(input, info, data->envp);
		if (function_return == LINE_IS_EMPTY)
			return (FUNCTION_SUCCESS); // faut free des trucs tho
		if (function_return != FUNCTION_SUCCESS)
			return (ft_error(function_return));
		if (!ft_check_syntax_with_tokens(info->tokens))
			ft_error(SYNTAX_TOKEN_ERROR);
		else
		{
			ft_display_lexer(*info);
			// function_return = ft_parser(info, data); // attention, on va avoir une verif a faire
			//if (function_return != FUNCTION_SUCCESS)
			//	return (ft_error(function_return, data, info));
		}
		ft_clean_info_bis(&info);
	}
	(void)data;
	return (FUNCTION_SUCCESS);
}

