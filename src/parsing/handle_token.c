/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 14:00:29 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/12 14:39:34 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenizer.h"
#include "../../incl/env.h"

int	next_whitespace(char *input, int i)
{
	int	count;

	count = 0;
	while (input[i] && !ft_isspace(input[i]))
	{
		i++;
		count++;
	}
	return (count);
}

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

void	assign_var(t_token *token, char *input, int i, t_env_list *env_lst)
{
	t_env_list	*curr;
	char		*key;

	curr = env_lst;
	key = ft_substr(input, i, next_whitespace(input, i) + i);
	while (curr)
	{
		if (!ft_strncmp(curr->key, key, next_whitespace(input, i)))
		{
			free(key);
			token->value = ft_strdup(curr->value);
			token->expand = true;
			return ;
		}
		curr = curr->next;
	}
	free(key);
	token->value = ft_strdup("");
	token->expand = true;
}

t_token	handle_brackets(int i, char *input, t_token token, t_env_list *env_lst)
{
	char	bracket;
	int		j;

	j = 0;
	printf("token->value: %s\n", token.value);
	if (input[i] == '-')
		j = assign_minus(&token, input, i);
	else if (input[i] == '$')
	{
		assign_var(&token, input, i + 1, env_lst);
		return (token);
	}
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
	while (i < i_len && !ft_isspace(input[i]) && input[i] != '|' && !ft_isredir(input[i]))
	{
		token.value[j] = input[i];
		i++;
		j++;
	}
	token.value[j] = '\0';
	check_new_cmd(&token);
	return (token);
}
