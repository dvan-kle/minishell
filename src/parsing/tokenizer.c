/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 15:33:45 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/27 22:36:27 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenizer.h"

t_token	handle_brackets(int i, char *input, t_token token)
{
	char	bracket;
	int		j;

	j = 0;
	if (input[i] == '-')
		j = assign_minus(&token, input, i);
	else
	{
		bracket = input[i];
		i++;
		j = assign_bracket(&token, input, i, bracket);
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
	if (input[i] == '<' || input[i] == '>' || input[i] == '|')
	{
		assign_token(&token, input, i);
		return (token);
	}
	token.value = malloc(sizeof(char) * malloc_count(input, i, '|') + 1);
	if (!token.value)
		exit(1);
	while (i < i_len && !ft_isspace(input[i]) && input[i] != '|')
	{
		token.value[j] = input[i];
		i++;
		j++;
	}
	token.value[j] = '\0';
	check_new_cmd(&token);
	return (token);
}

t_token	tokenize(t_token token, char *input)
{
	size_t	i;
	int		whitespaces;

	i = 0;
	whitespaces = 0;
	token.next = NULL;
	while (i < ft_strlen(input) && ft_isspace(input[i]))
	{
		i++;
		whitespaces++;
	}
	if (i == ft_strlen(input))
	{
		token.type = END_OF_CMD_TOKEN;
		token.value = malloc(sizeof(char) * 1);
		if (!token.value)
			exit(1);
		ft_strlcpy(token.value, "", 1);
		return (token);
	}
	if (input[i] == '"' || input[i] == '\'' || input[i] == '-')
		token = handle_brackets(i, input, token);
	else
		token = handle_rest(i, input, token);
	token.whitespaces = whitespaces;
	return (token);
}

t_token	*lexer(char *input)
{
	t_token			*token_list;
	t_token			token;

	token_list = NULL;
	init_token(&token);
	while (token.type != END_OF_CMD_TOKEN)
	{
		token = tokenize(token, input);
		token_list = list_add_back(token_list, token);
		input += ft_strlen(token.value) + token.whitespaces;
		if (token.brackets == true)
		{
			input += 2;
			token.brackets = false;
		}
	}
	//print_list(token_list);
	return (token_list);
}
