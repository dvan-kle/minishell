/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 17:43:42 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/27 18:38:00 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenizer.h"
#include "../../libft/libft.h"

void	init_token(t_token *token)
{
	token->type = ARGUMENT_TOKEN;
	token->brackets = false;
	token->new_cmd = true;
	token->next = NULL;
	token->value = NULL;
}

int	malloc_count(char *str, int i, char c)
{
	int	count;

	count = 0;
	while (str[i] && !ft_isspace(str[i]) && str[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}
