/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/13 14:53:20 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/14 15:12:43 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenizer.h"

int	next_whitespace(char *input, int i)
{
	int	count;

	count = 0;
	while (input[i] && !ft_isspace(input[i]))
	{
		i++;
		count++;
	}
	return (count);
}

int	next_whitespace_and_bracket(char *input, int i)
{
	int	count;

	count = 0;
	while (input[i] && !ft_isspace(input[i]) && input[i] != '\"')
	{
		i++;
		count++;
	}
	return (count);
}

t_token	check_new_cmd(t_token *token)
{
	if (token->new_cmd == true)
	{
		token->type = CMD_TOKEN;
		token->new_cmd = false;
	}
	else
		token->type = ARGUMENT_TOKEN;
	return (*token);
}
