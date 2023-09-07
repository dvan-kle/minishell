/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 15:33:45 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/01 18:04:17 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenizer.h"
#include "../../incl/env.h"

t_token	tokenize(t_token token, char *input, t_env_list *env_list)
{
	size_t	i;

	i = 0;
	token.whitespaces = 0;
	token.next = NULL;
	while (i < ft_strlen(input) && ft_isspace(input[i]))
	{
		i++;
		token.whitespaces++;
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
	if (input[i] == '"' || input[i] == '\'' || input[i] == '-'
		|| input[i] == '$')
		token = handle_brackets(i, input, token, env_list);
	else
		token = handle_rest(i, input, token);
	return (token);
}

t_token	*lexer(char *input, t_env_list *env_list)
{
	t_token			*token_list;
	t_token			token;

	token_list = NULL;
	init_token(&token);
	while (token.type != END_OF_CMD_TOKEN)
	{
		token = tokenize(token, input, env_list);
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
