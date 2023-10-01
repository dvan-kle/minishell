/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 15:33:45 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/01 21:36:33 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenizer.h"
#include "../../incl/env.h"

t_token	tokenize(t_token token, char *input, int exit_status)
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
		token.value = ft_malloc(sizeof(char) * 1);
		ft_strlcpy(token.value, "", 1);
		return (token);
	}
	if (input[i] == '"' || input[i] == '\'' || input[i] == '-'
		|| input[i] == '$')
		token = handle_brackets(i, input, token, exit_status);
	else
		token = handle_rest(i, input, token);
	return (token);
}

t_token	*lexer(char *input, t_env_list *env_list, int exit_status)
{
	t_token			*token_list;
	t_token			token;

	token_list = NULL;
	init_token(&token, env_list);
	while (token.type != END_OF_CMD_TOKEN)
	{
		//printf("input: %s\n", input);
		token = tokenize(token, input, exit_status);
		token_list = list_add_back(token_list, token);
		if (token.type == END_OF_CMD_TOKEN)
			break ;
		input += update_input(&token, input);
	}
	return (token_list);
}
