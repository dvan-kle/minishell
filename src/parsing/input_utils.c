/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 13:56:04 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/01 21:23:11 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenizer.h"

int	count_brackets(char *input)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (ft_isspace(input[i]))
		i++;
	while (input[i] == '\"' || input[i] == '\'')
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

int	update_input(t_token *token, char *input)
{
	int		i;
	char	bracket;

	i = 0;
	if (token->expand == true)
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		while (input[i] == '\"' || input[i] == '\'' || input[i] == '$')
		{
			if (input[i] != '$')
			{
				bracket = input[i];
				i++;
				while (input[i] && input[i] != bracket)
					i++;
				if (input[i] && input[i] == bracket)
					i++;
			}
			else
				i += next_whitespace_brackets(input, i + 1) + 1;
			
		}
		token->expand = false;
	}
	else
		i += ft_strlen(token->value) + token->whitespaces;
	if (token->brackets == true)
	{
		i += count_brackets(input) * 2;
		token->brackets = false;
	}
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
