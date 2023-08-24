/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assign_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 18:56:56 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/24 18:56:57 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenizer.h"

int	assign_token(t_token *token, char *type, int i)
{
	token->value[0] = type[i];
	token->value[1] = '\0';
	if (type[i] == '<')
	{
		if (type[i + 1] == '<')
		{
			token->value[1] = type[i + 1];
			token->value[2] = '\0';
			token->type = READ_INPUT_TOKEN;
			return (1);
		}
		else
			token->type = INPUT_REDIRECT_TOKEN;
	}
	else if (type[i] == '|')
	{
		token->type = PIPE_TOKEN;
		token->new_cmd = true;
	}
	else if (type[i] == '>')
	{
		if (type[i + 1] == '>')
		{
			token->value[1] = type[i + 1];
			token->value[2] = '\0';
			token->type = OUTPUT_REDIRECT_APPEND_TOKEN;
			return (1);
		}
		else
			token->type = OUTPUT_REDIRECT_TOKEN;
	}
	return (0);
}

int	assign_minus(t_token *token, char *type, int i)
{
	int		input_len;
	int		j;

	input_len = ft_strlen(type);
	j = 0;
	while (i < input_len && !ft_isspace(type[i]) && j < MAX_LEN)
	{
		token->value[j] = type[i];
		i++;
		j++;
	}
	return (j);
}

int	assign_bracket(t_token *token, char *type, int i, char bracket)
{
	int		input_len;
	int		j;

	input_len = ft_strlen(type);
	j = 0;
	while (i < input_len && type[i] != bracket && j < MAX_LEN)
	{
		token->value[j] = type[i];
		i++;
		j++;
	}
	return (j);
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
