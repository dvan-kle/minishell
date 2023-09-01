/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 14:00:29 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/01 18:49:04 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenizer.h"
#include "../../incl/env.h"

// this function is not good yet :).
int	assign_var(t_token *token, char *input, int i, t_env_list *env_lst)
{
	t_env_list	*curr;

	curr = env_lst;
	while (env_lst->next != NULL)
	{
		//printf("%s\n", env_lst->key);
		printf("%zu\n", ft_strlen(input));
		if (env_lst->key == ft_substr(input, i + 1, ft_strlen(input)))
		{
			token->value = ft_substr(env_lst->value, 0, ft_strlen(env_lst->value));
			token->type = ARGUMENT_TOKEN;
			return (ft_strlen(env_lst->key) + 1);
		}
		env_lst = env_lst->next;
	}
	printf("%s\n", token->value);
	return (1);
}

t_token	handle_brackets(int i, char *input, t_token token, t_env_list *env_lst)
{
	char	bracket;
	int		j;

	j = 0;
	if (input[i] == '-')
		j = assign_minus(&token, input, i);
	else if (input[i] == '$')
		j = assign_var(&token, input, i, env_lst);
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
