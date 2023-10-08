
#include "minishell.h"
#include "minishell_louis.h"

int	ft_remove_quotes(t_list *list, char quote)
{
	t_token	*current_token;
	char	*curr_word;

	current_token = (t_token *)list->content;
	printf("%s\n", current_token->string);
	if (!ft_check_empty_line(&current_token->string[1], (ft_strlen(current_token->string) -1)))
		return (FUNCTION_SUCCESS);
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

	current_token->join_with_next = true;
	curr_word = ft_substr(current_token->string, 0, i);
	if (!curr_word)
		return (MEMORY_ERROR_PT);//careful
	if (ft_is_quote(curr_word[0]))
	{
		if (!ft_check_empty_line(&current_token->string[1], (ft_strlen(current_token->string) -1)))
			return (curr_word);	
		if (quote == DOUBLE_QUOTE)
			truncate_quote =  ft_strtrim(curr_word, "\"");
		else
			truncate_quote =  ft_strtrim(curr_word, "'");
		free (curr_word);
		if (!truncate_quote)
			return (MEMORY_ERROR_PT); //careful
		return (truncate_quote);
	}
	else
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
		if(!current_token->string[i]) // si jamais ya rien a split, on enleve juste les quote
			return (ft_remove_quotes(list, quote));
			//return(FUNCTION_SUCCESS);
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

int	ft_retreat_lexer(t_list *list)
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

int	ft_del_quotes(t_info *info)
{
	t_list	*list;
	t_token	*current_token;

	list = info->tokens;
	while (list)
	{
		current_token = (t_token *)list->content;
		if (current_token->type == type_word)
		{
			if (ft_retreat_lexer(list) != FUNCTION_SUCCESS)
				return (MEMORY_ERROR_NB); // attention, mal clean
		}
		list = list->next;
	}
	return (FUNCTION_SUCCESS);
}

int	ft_lexer(const char *input, t_info *info)
{
	int		i;
	t_list	*new_node;
	t_token	*new_token;

	i = 0;
	while (input[i]) //remplir le tableau de mots
	{
		if (!ft_check_empty_line(input, i))
			break;
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (MEMORY_ERROR_NB);
		new_token->string = NULL;
		new_token->string = get_token_val(input, &i); //verif a faire
		new_token->type = get_token_type(new_token->string);
		new_token->expand = false;
		new_token->join_with_next = false;
		new_token->quote = no_q;
		new_node = ft_lstnew((void *)new_token);
		if(!new_node)
			return (MEMORY_ERROR_NB);
		ft_lstadd_back(&info->tokens, new_node);
	}
	ft_display_lexer(*info);
	printf(BLUE"\nSeparage des quotes\n"NC);
	ft_del_quotes(info);
	ft_display_lexer(*info);
	//manager lexpand
	return (FUNCTION_SUCCESS);
}

/* main de vérif de fonctions 

int	main(void)
{
	char *str = ">grrrr omg<jpppp ohlala |< > 'putain|de|merde hihi cest encore la meme quote'\"encore la aussi\"|mais plus maintenant hihi |'grr'> <";
	int	nb_tokens;

	nb_tokens = ft_count_token(str);
	printf("nb tokens : %d\n", nb_tokens);
	int i = 0;
	int size = -1;
	while (size)
	{
		size = ft_get_token_val_len(str, &i);
		printf("size = %d\n", size);
	}	
}
*/

// int	main(void)
// {
// 	char *str = ">grrrr omg<jpppp ohlala |< > 'putain|de|merde hihi cest encore la meme quote'\"encore la aussi\"|mais plus maintenant hihi |'grr'> <";
// 	t_info	info;
// 	lexer(str, &info);
// 	int i = 0;
// 	printf("nb mots : %d\n", info.nb_tokens);
// 	while (i < info.nb_tokens)
// 	{
// 		printf("mot : %s, type : %d\n", info.tokens[i]->string, info.tokens[i]->type);
// 		i++;
// 	}
// }