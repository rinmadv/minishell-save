
#include "minishell.h"
#include "minishell_louis.h"

int	parsing(t_data *data, const char *input)
{
	t_info	*info;

	info = NULL;
	if (ft_check_open_quote_bool(input) || !ft_check_empty_line(input, 0))
		return (FUNCTION_SUCCESS);
	info = create_info(info);
	if (!info)
		return (MEMORY_ERROR_NB);
	if (ft_tokenise(input, info))
		return (ft_clean_info_bis(&info), info = NULL, MEMORY_ERROR_NB);
	if (ft_check_syntax_with_tokens(info->tokens))
	{
		if (ft_del_quotes(info) || ft_expand(info, data->envp, data)
			|| ft_join_nodes(info->tokens) || ft_interprete(info, data))
			return (ft_clean_info_bis(&info), info = NULL, MEMORY_ERROR_NB); //ici aussi surement reinit data
	}
	ft_clean_info_bis(&info);
	info = NULL;
	return (FUNCTION_SUCCESS);
}
