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

bool	ft_isredirect(t_tokentype type)
{
	if (type == INPUT_REDIRECT_TOKEN || type == OUTPUT_REDIRECT_TOKEN
		|| type == APPEND_TOKEN || type == READ_INPUT_TOKEN)
		return (true);
	return (false);
}

void	init_token(t_token *token)
{
	token->type = ARGUMENT_TOKEN;
	token->brackets = false;
	token->new_cmd = true;
	token->next = NULL;
	token->value = NULL;
}
