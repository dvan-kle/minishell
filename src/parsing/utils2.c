/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/13 14:53:20 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/13 15:44:49 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenizer.h"

bool	find_key(t_token *token, char *key, char *input)
{
	t_env_list	*curr;

	curr = token->env_lst;
	while (curr)
	{
		if (!ft_strncmp(curr->key, key, next_whitespace(input, 0)))
			return (true);
		curr = curr->next;
	}
	return (false);
}
