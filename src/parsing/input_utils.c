/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 13:56:04 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/09 21:32:10 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

int	count_brackets(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (ft_isspace(input[i]))
		i++;
	while ((input[i] == '\"' || input[i] == '\''))
	{
		i++;
		while (input[i] && input[i] != '\"' && input[i] != '\'')
			i++;
		if (input[i] && (input[i] == '\"' || input[i] == '\''))
			i++;
		count++;
	}
	return (count);
}

int	loop_until_bracket(char *input, int i, char bracket)
{
	int	count;

	count = 1;
	i++;
	while (input[i] && input[i] != bracket)
	{
		i++;
		count++;
	}
	if (input[i] && input[i] == bracket)
	{
		i++;
		count++;
	}
	return (count);
}

int	update_input(t_token *token, char *input)
{
	int		i;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (token->expand == true)
	{
		while (input[i] && (input[i] == '\"' || input[i] == '\''
				|| input[i] == '$'))
		{
			if (input[i] == '$')
				i += next_whitespace_brackets(input, i + 1) + 1;
			else
				i += loop_until_bracket(input, i, input[i]);
		}
		token->expand = false;
	}
	else
		i += ft_strlen(token->value) + (count_brackets(input) * 2);
	return (i);
}

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

int	next_whitespace_brackets(char *input, int i)
{
	int	count;

	count = 0;
	while (input[i] && !ft_isspace(input[i]) && input[i] != '\"' && input[i]
		!= '\'' && input[i] != '$')
	{
		i++;
		count++;
	}
	return (count);
}
