/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 15:33:45 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/07/25 18:01:00 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdio.h>

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

t_token	handle_brackets(int i, int j, char *input)
{
	t_token	token;
	char	bracket;
	int		input_len;

	bracket = input[i];
	input_len = ft_strlen(input);
	i++;
	j = 0;
	while (i < input_len && input[i] != bracket && j < MAX_LEN)
	{
		token.value[j] = input[i];
		i++;
		j++;
	}
	token.value[j] = '\0';
	token.type = CMD_TOKEN;
	return (token);
}

t_token	handle_rest(int i, int j, char *input)
{
	int		i_len;
	t_token	token;

	i_len = ft_strlen(input);
	j = 0;
	while (i < i_len && !ft_isspace(input[i]) && input[i] != '>' && input[i] != '<' && input[i] != '|')
	{
		token.value[j] = input[i];
		i++;
		j++;
	}
	token.value[j] = '\0';
	if (input[i] == '>')
		token.type = OUTPUT_REDIRECT_TOKEN;
	else if (input[i] == '<')
		token.type = INPUT_REDIRECT_TOKEN;
	else if (input[i] == '|')
		token.type = PIPE_TOKEN;
	else
		token.type = CMD_TOKEN;
	return (token);
}

t_token	tokenize(char *input)
{
	t_token	token;
	int		i;
	int		j;
	int		input_len;

	i = 0;
	j = 0;
	ft_strlcpy(token.value, "", 1);
	token.type = CMD_TOKEN;
	input_len = ft_strlen(input);
	while (i < input_len && ft_isspace(input[i]))
		i++;
	if (i == input_len)
	{
		token.type = END_OF_CMD_TOKEN;
		ft_strlcpy(token.value, "", 1);
		return (token);
	}
	if (input[i] == '"' || input[i] == '\'')
		token = handle_brackets(i, j, input);
	else
		token = handle_rest(i, j, input);
	return (token);
}

int	main(void)
{
	char	*input;
	t_token	token;

	input = "ls -l > output.txt";
	
	token = tokenize(input);
	ft_printf("Type: %d, Value: %s\n", token.type, token.value);
	input += ft_strlen(token.value) + 1;
	while (token.type != END_OF_CMD_TOKEN)
	{
		token = tokenize(input);
		ft_printf("Type: %d, Value: %s\n", token.type, token.value);
		input += ft_strlen(token.value) + 1;
	}
}
