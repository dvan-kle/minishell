/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 17:33:18 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/11 17:34:53 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

char	*check_for_key(char *key, t_env_list *curr,
			t_token *token, int exit_status)
{
	char	*result;

	result = NULL;
	if (!ft_strncmp(key, "?", ft_strlen(key) + 1))
	{
		free(key);
		result = ft_itoa(exit_status);
		token->expand = true;
		return (result);
	}
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
	return (NULL);
}

char	*assign_var(t_token *token, char *input, int i, int exit_status)
{
	t_env_list	*curr;
	char		*key;
	char		*result;

	curr = token->env_lst;
	key = ft_substr(input, i, next_whitespace_brackets(input, i));
	result = check_for_key(key, curr, token, exit_status);
	if (result)
		return (result);
	free(key);
	return (result);
}

int	add_key_to_token(t_token *token, char *input, int i)
{
	char	*key;

	key = assign_var(token, input, i + 1, 0);
	token->value = minishell_strjoin(token->value, key);
	token->expand = true;
	i += next_whitespace_brackets(input, i + 1) + 1;
	return (i);
}

bool	nothing_after_dollar(char *input, int i)
{
	if (!input[i + 1] || ft_isspace(input[i + 1])
		|| is_meta(input[i + 1]) || ft_isredir(input[i + 1]))
		return (true);
	return (false);
}
