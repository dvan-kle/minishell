/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 14:00:29 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/09 21:32:06 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

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

char	*check_for_key(char *key, t_env_list *curr, t_token *token, int exit_status)
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

char	*ft_strjoin2(char const *str1, char const *str2)
{
	char	*ptr;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = ft_strlen(str1) + ft_strlen(str2) + 1;
	if (!str1)
		str1 = ft_strdup("");
	if (!str2)
		str2 = ft_strdup("");
	ptr = ft_malloc((sizeof(char) * k));
	while (str1[i])
	{
		ptr[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		ptr[i + j] = str2[j];
		j++;
	}
	ptr[i + j] = '\0';
	free((char *)str1);
	if (ft_strncmp(str2, "$", 2))
		free((char *)str2);
	return (ptr);
}

t_token	handle_brackets(int i, char *input, t_token token, int exit_status)
{
	token.value = NULL;
	if (input[i] == '-')
		assign_minus(&token, input, i);
	else if (input[i] == '$')
	{
		while (input[i] && input[i] == '$')
		{
			if (!input[i + 1] || ft_isspace(input[i + 1]) || input[i + 1] == '|'
				|| input[i + 1] == '$')
			{
				token.value = ft_strjoin2(token.value, "$");
				i++;
			}
			else
			{
				token.value = ft_strjoin2(token.value, assign_var(&token, input, i + 1, exit_status));
				i += next_whitespace_brackets(input, i + 1) + 1;
				token.expand = true;
			}
		}
	}
	else
		assign_bracket(&token, input, i);
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
