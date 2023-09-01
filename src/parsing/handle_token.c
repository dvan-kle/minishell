/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 14:00:29 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/31 17:24:46 by tde-brui      ########   odam.nl         */
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
