
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
		return (printf("cc\n"), LINE_IS_EMPTY);
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

void	ft_change_join_bool(t_list *prev, t_list *curr)
{
	t_token	*curr_token;
	t_token	*prev_token;

	curr_token = (t_token *)curr->content;
	prev_token = (t_token *)prev->content;
	if (prev_token->join_with_next && !curr_token->join_with_next)
		prev_token->join_with_next = false;
}

int	ft_retreat_lexer(t_info *info)
{
	t_list	*list;
	t_token	*current_token;
	t_list	*prev;
	t_list	*tmp;

	list = info->tokens;
	prev = NULL;
	while (list)
	{
		current_token = (t_token *)list->content;
		if (current_token->type == type_word)
		{
			if (ft_split_quotes(list) != FUNCTION_SUCCESS)
				return (MEMORY_ERROR_NB); // attention, mal clean
			if (current_token->quote && ft_remove_quotes(list, current_token->string[0]) == LINE_IS_EMPTY)
			{
				if (prev)
				{
				//checker pour les joint
				ft_change_join_bool(prev, list);
				//changer les next
				prev->next = list->next;
				// //delete ce node
				free(current_token->string);
				free(current_token);
				free(list); // attention si jamais on était au premier ""
				list = prev;
				}
				else
				{
					tmp = list->next;
					free(list);
					list = tmp;
				}
			}
		}
		if (!list)
			return (LINE_IS_EMPTY);
		prev = list;
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
	int rez;
	rez = ft_retreat_lexer(info); // add secu
	if (rez == MEMORY_ERROR_NB)
		return (MEMORY_ERROR_NB);
	if (rez == LINE_IS_EMPTY)
		return (LINE_IS_EMPTY);
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