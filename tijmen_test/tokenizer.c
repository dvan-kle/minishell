/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 15:33:45 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/07/29 14:47:34 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "tokenizer.h"

#include <stdbool.h>
#include <stdio.h>

#define MAX_LEN 100

typedef enum token_type{
	CMD_TOKEN,
	ARGUMENT_TOKEN,
	INPUT_REDIRECT_TOKEN,
	OUTPUT_REDIRECT_TOKEN,
	PIPE_TOKEN,
	END_OF_CMD_TOKEN,
	READ_INPUT_TOKEN,
	OUTPUT_REDIRECT_APPEND_TOKEN
}t_tokentype;

typedef struct token{
	t_tokentype	type;
	char		value[MAX_LEN];
	bool		brackets;
	bool		new_cmd;
}t_token;

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == 9)
		return (1);
	if (c == 10)
		return (1);
	if (c == 11)
		return (1);
	if (c == 12)
		return (1);
	if (c == 13)
		return (1);
	return (0);
}

t_token	handle_brackets(int i, char *input, t_token token)
{
	char	bracket;
	int		input_len;
	int		j;

	bracket = input[i];
	input_len = ft_strlen(input);
	j = 0;
	if (input[i] == '-')
	{
		while (i < input_len && !ft_isspace(input[i]) && j < MAX_LEN)
		{
			token.value[j] = input[i];
			i++;
			j++;
		}
	}
	else
	{
		i++;
		while (i < input_len && input[i] != bracket && j < MAX_LEN)
		{
			token.value[j] = input[i];
			i++;
			j++;
		}
		token.brackets = true;
	}
	token.value[j] = '\0';
	token.type = ARGUMENT_TOKEN;
	return (token);
}

t_token	handle_rest(int i, char *input, t_token token)
{
	int		i_len;
	int		j;

	i_len = ft_strlen(input);
	j = 0;
	while (i < i_len && !ft_isspace(input[i]) && input[i] != '>' && input[i] != '<' && input[i] != '|')
	{
		token.value[j] = input[i];
		i++;
		j++;
	}
	token.value[j] = '\0';
	if (input[i] == '>' || input[i] == '<' || input[i] == '|')
	{
		token.value[0] = input[i];
		token.value[1] = '\0';
		if (input[i] == '>')
			token.type = OUTPUT_REDIRECT_TOKEN;
		else if (input[i] == '<')
			token.type = INPUT_REDIRECT_TOKEN;
		else if (input[i] == '|')
		{
			token.type = PIPE_TOKEN;
			token.new_cmd = true;
		}
		i++;
	}
	else
	{
		if (token.new_cmd == true)
		{
			token.type = CMD_TOKEN;
			token.new_cmd = false;
		}
		else
			token.type = ARGUMENT_TOKEN;
	}
	return (token);
}

t_token	tokenize(t_token token, char *input)
{
	int		i;
	int		j;
	int		input_len;

	i = 0;
	j = 0;
	input_len = ft_strlen(input);
	while (i < input_len && ft_isspace(input[i]))
		i++;
	if (i == input_len)
	{
		token.type = END_OF_CMD_TOKEN;
		ft_strlcpy(token.value, "", 1);
		return (token);
	}
	if (input[i] == '"' || input[i] == '\'' || input[i] == '-')
		token = handle_brackets(i, input, token);
	else
		token = handle_rest(i, input, token);
	return (token);
}

void	lexer(void)
{
	char	*input;
	t_token	token;

	ft_strlcpy(token.value, "", 1);
	token.type = ARGUMENT_TOKEN;
	token.brackets = false;
	token.new_cmd = true;
	token = tokenize(token, input);
	ft_printf("Type: %d, Value: %s\n", token.type, token.value);
	input += ft_strlen(token.value);
	while (token.type != END_OF_CMD_TOKEN)
	{
		token = tokenize(token, input);
		ft_printf("Type: %d, Value: %s\n", token.type, token.value);
		input += ft_strlen(token.value) + 1;
		if (token.brackets == true)
			input += 2;
	}
}
