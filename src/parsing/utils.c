/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 17:43:42 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/30 19:18:11 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parser.h"
#include "../../libft/libft.h"

bool	ft_isredirect(t_tokentype type)
{
	if (type == INPUT_REDIRECT_TOKEN || type == OUTPUT_REDIRECT_TOKEN
		|| type == OUTPUT_REDIRECT_APPEND_TOKEN || type == READ_INPUT_TOKEN)
		return (true);
	return (false);
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

void	init_token(t_token *token)
{
	token->type = ARGUMENT_TOKEN;
	token->brackets = false;
	token->new_cmd = true;
	token->next = NULL;
	token->value = NULL;
}
