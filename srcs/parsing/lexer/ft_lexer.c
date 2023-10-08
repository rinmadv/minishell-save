
#include "minishell.h"
#include "minishell_louis.h"

bool	ft_check_empty_line_quote(const char *str, int i)
{
	i++;
	while (str[i])
	{
		if (str[i] > 32 && str[i+1] != 0)
			return (true);
		i++;
	}
	return (false);
}

int	ft_remove_quotes(t_list *list, char quote)
{
	t_token	*current_token;
	char	*curr_word;

	current_token = (t_token *)list->content;
	if (!ft_check_empty_line_quote(current_token->string, 0))
		return (LINE_IS_EMPTY);
	if (quote == DOUBLE_QUOTE)
	{
		current_token->quote = double_q;
		curr_word =  ft_strtrim(current_token->string, "\"");
	}
	else
	{
		current_token->quote = simple_q;
		curr_word = ft_strtrim(current_token->string, "'");
	}
	if (!current_token->string)
		return (MEMORY_ERROR_NB);
	free(current_token->string);
	current_token->string = curr_word;
	return (FUNCTION_SUCCESS); // attention a bien free
}

char	*ft_change_current_str(t_token *current_token, int i, char quote)
{
	char	*curr_word;
	char	*truncate_quote;
	(void) truncate_quote;
	(void) quote;
	current_token->join_with_next = true;
	curr_word = ft_substr(current_token->string, 0, i);
	if (!curr_word)
		return (MEMORY_ERROR_PT);//careful
	if (current_token->string[0] == quote)
		current_token->quote = true_q;
	return (curr_word);
}
void	ft_get_i(char quote, char *string, int *i)
{ // on aura peut etre un segfault ici car on check pas si /0
	*i += 1;
	while (string[*i] != quote)
		*i += 1;
	*i += 1;
}

int	ft_insert_next_node(int i, t_list *list)
{
	t_token	*current_token;
	t_token *new_token;
	char	*new_word;
	t_list	*new;

	current_token = (t_token *)list->content;
	new_word = ft_substr(current_token->string, i, ft_strlen(current_token->string));
	if (!new_word)
		return (MEMORY_ERROR_NB);//careful
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (MEMORY_ERROR_NB);
	new_token->string = new_word;
	new_token->type = type_word;
	new_token->expand = false;
	new_token->join_with_next = false;
	new_token->quote = false;
	new = ft_lstnew((void *)new_token);
	if (!new)
		return (MEMORY_ERROR_NB);
	new->next = list->next;
	list->next = new;
	return (FUNCTION_SUCCESS);
}

int	ft_detach_quotes(int i, t_list *list, char quote)
{
	char	*curr_word;
	t_token	*current_token;

	curr_word = NULL;
	current_token = (t_token *)list->content;
	if (i == 0) //on est dans une quote + c'est la premiere
	{
		ft_get_i(quote, current_token->string, &i);
		if (current_token->string[0] == quote)
			current_token->quote = true_q;
		if(!current_token->string[i]) // si jamais ya rien a split, on return
			return (FUNCTION_SUCCESS);
	}
	if (ft_insert_next_node(i, list) != FUNCTION_SUCCESS)
		return (MEMORY_ERROR_NB);
	curr_word = ft_change_current_str(current_token, i, quote);
	if (!curr_word)
		return (MEMORY_ERROR_NB);
	free(current_token->string);
	current_token->string = curr_word;
	return (FUNCTION_SUCCESS);
}

int	ft_split_quotes(t_list *list)
{
	t_token	*current_token;
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	current_token = (t_token *)list->content;
	while (current_token->string[i] && !quote) 
	{
		quote = ft_is_quote(current_token->string[i]);
		if (quote)
			return (ft_detach_quotes(i, list, quote));
		i++;
	}
	return (FUNCTION_SUCCESS);
}

int	ft_retreat_lexer(t_info *info)
{
	t_list	*list;
	t_token	*current_token;

	list = info->tokens;
	while (list)
	{
		current_token = (t_token *)list->content;
		if (current_token->type == type_word)
		{
			if (ft_split_quotes(list) != FUNCTION_SUCCESS)
				return (MEMORY_ERROR_NB); // attention, mal clean
			if (current_token->quote && ft_remove_quotes(list, current_token->string[0]) == LINE_IS_EMPTY)
				current_token->empty_node = true;
		}
		list = list->next;
	}
	return (FUNCTION_SUCCESS);
}

int	ft_init_token(t_token *new_token, const char *input, int *i)
{
	new_token->string = NULL;
	new_token->string = get_token_val(input, i);
	if (!new_token->string)
		return (MEMORY_ERROR_NB); //free des trucs aussi
	new_token->type = get_token_type(new_token->string);
	new_token->expand = false;
	new_token->join_with_next = false;
	new_token->quote = no_q;
	new_token->empty_node = false;
	return (FUNCTION_SUCCESS);
}

int	ft_lexer(const char *input, t_info *info)
{
	int		i;
	t_list	*new_node;
	t_token	*new_token;

	i = 0;
	while (input[i])
	{
		if (!ft_check_empty_line(input, i))
			break;
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (MEMORY_ERROR_NB);
		if (ft_init_token(new_token, input, &i) != FUNCTION_SUCCESS)
			return (MEMORY_ERROR_NB); //penser a bien free
		new_node = ft_lstnew((void *)new_token);
		if(!new_node)
			return (MEMORY_ERROR_NB);
		ft_lstadd_back(&info->tokens, new_node);
	}
	if (ft_retreat_lexer(info) != FUNCTION_SUCCESS) 
		return (MEMORY_ERROR_NB);
	//manager lexpand
	return (FUNCTION_SUCCESS);
}
