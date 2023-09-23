/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 14:00:29 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/23 16:08:28 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenizer.h"
#include "../../incl/env.h"

int	get_env_len(t_env_list *env_lst)
{
	int	count;

	count = 0;
	while (env_lst->next != NULL)
	{
		count++;
		env_lst = env_lst->next;
	}
	return (count);
}

char	*assign_var(t_token *token, char *input, int i)
{
	t_env_list	*curr;
	char		*key;
	char		*result;

	curr = token->env_lst;
	key = ft_substr(input, i, next_whitespace_and_bracket(input, i));
	// if (!ft_strncmp(key, "?", ft_strlen(key) + 1))
	// {
	// 	free(key);
	// 	result = ft_itoa(token->error);
	// 	token->expand = true;
	// 	return (result);
	// }
	result = ft_strdup("");
	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(curr->key) + 1))
		{
			free(key);
			result = ft_strdup(curr->value);
			token->expand = true;
			return (result);
		}
		curr = curr->next;
	}
	free(key);
	token->expand = true;
	return (result);
}

t_token	handle_brackets(int i, char *input, t_token token)
{
	char	bracket;

	if (input[i] == '-')
		assign_minus(&token, input, i);
	else if (input[i] == '$')
		token.value = assign_var(&token, input, i + 1);
	else
	{
		bracket = input[i];
		i++;
		assign_bracket(&token, input, i, bracket);
	}
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
	token.value = ft_malloc(sizeof(char) * malloc_count(input, i, '|') + 1);
	while (i < i_len && !ft_isspace(input[i])
		&& input[i] != '|' && !ft_isredir(input[i]))
	{
		token.value[j] = input[i];
		i++;
		j++;
	}
	token.value[j] = '\0';
	check_new_cmd(&token);
	return (token);
}
