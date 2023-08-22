/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 15:33:45 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/22 17:56:14 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenizer.h"

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
	while (i < i_len && !ft_isspace(input[i])
		&& input[i] != '>' && input[i] != '<' && input[i] != '|')
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
		if (input[i] == '<')
		{
			if (input[i] + 1 == '<')
			{
				token.value[1] = input[i + 1];
				token.value[2] = '\0';
				token.type = READ_INPUT_TOKEN;
			}
			else
				token.type = INPUT_REDIRECT_TOKEN;
		}
		else if (input[i] == '|')
		{
			token.type = PIPE_TOKEN;
			token.new_cmd = true;
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				token.value[1] = input[i + 1];
				token.value[2] = '\0';
				token.type = OUTPUT_REDIRECT_APPEND_TOKEN;
				i++;
			}
			else
				token.type = OUTPUT_REDIRECT_TOKEN;
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
	token.next = NULL;
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

t_token	*lexer(char *input)
{
	t_token			*token_list;
	t_token			token;

	token_list = NULL;
	init_token(&token);
	token = tokenize(token, input);
	token_list = list_add_back(token_list, token);
	input += ft_strlen(token.value);
	while (token.type != END_OF_CMD_TOKEN)
	{
		token = tokenize(token, input);
		token_list = list_add_back(token_list, token);
		input += ft_strlen(token.value) + 1;
		if (token.brackets == true)
		{
			input += 2;
			token.brackets = false;
		}
	}
	print_list(token_list);
	return (token_list);
}
