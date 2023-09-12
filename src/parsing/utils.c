/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 17:43:42 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/31 17:24:29 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parser.h"
#include "../../libft/libft.h"
#include "../../incl/tokenizer.h"

void	init_token(t_token *token)
{
	token->type = ARGUMENT_TOKEN;
	token->brackets = false;
	token->new_cmd = true;
	token->next = NULL;
	token->value = NULL;
	token->expand = false;
}

int	malloc_count(char *str, int i, char c)
{
	int	count;

	count = 0;
	while (str[i] && !ft_isspace(str[i])
		&& str[i] != c && !ft_isredirect(str[i]))
	{
		count++;
		i++;
	}
	return (count);
}

int	redir_count(t_token *lst);

int	allocate_cmd_table(t_cmd_table *cmd_table, t_token *lst)
{
	cmd_table->args = malloc(sizeof(char *) * (arg_token_count(lst) + 1));
	if (!cmd_table->args)
		return (1);
	cmd_table->redirects = malloc(sizeof(t_redirect) * (redir_count(lst) + 1));
	if (!cmd_table->redirects)
		return (1);
	cmd_table = cmd_table->next;
	return (0);
}

int	arg_token_count(t_token *to_be_added)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = to_be_added;
	while (curr)
	{
		if (curr->type == ARGUMENT_TOKEN || curr->type == CMD_TOKEN)
			count++;
		curr = curr->next;
	}
	return (count);
}

int	update_input(t_token token, char *input)
{
	int	i;

	i = 0;
	if (token.expand == true)
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		i += next_whitespace(input, i);
		token.expand = false;
	}
	else
		i += ft_strlen(token.value) + token.whitespaces;
	if (token.brackets == true)
	{
		i += 2;
		token.brackets = false;
	}
	return (i);
}
