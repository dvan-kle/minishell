/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 17:43:42 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/17 17:44:22 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenizer.h"
#include "../libft/libft.h"

void	init_token(t_token *token)
{
	ft_strlcpy(token->value, "", 1);
	token->type = ARGUMENT_TOKEN;
	token->brackets = false;
	token->new_cmd = true;
	token->next = NULL;
}
