/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assign_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 18:56:56 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/13 17:21:37 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenizer.h"

void	assign_redirect(t_token *token, char *type, int i,
t_tokentype first)
{
	if (type[i + 1] == type[i])
	{
		token->value[1] = type[i + 1];
		token->value[2] = '\0';
		token->type = first;
	}
	else
		token->type = first - 3;
}

void	assign_token(t_token *token, char *type, int i)
{
	if (ft_isspace(type[i + 1]) || !type[i])
		token->value = ft_malloc(sizeof(char) * 2);
	else
		token->value = ft_malloc(sizeof(char) * 3);
	token->value[0] = type[i];
	token->value[1] = '\0';
	if (type[i] == '<')
		assign_redirect(token, type, i, READ_INPUT_TOKEN);
	else if (type[i] == '|')
	{
		token->value[0] = '|';
		token->value[1] = '\0';
		token->type = PIPE_TOKEN;
		token->new_cmd = true;
	}
	else if (type[i] == '>')
		assign_redirect(token, type, i, APPEND_TOKEN);
}

int	assign_minus(t_token *token, char *type, int i)
{
	int		input_len;
	int		j;

	token->value = ft_malloc(sizeof(char) * malloc_count(type, i, '|') + 1);
	input_len = ft_strlen(type);
	j = 0;
	while (i < input_len && !ft_isspace(type[i]) && type[i] != '|'
		&& !ft_isredir(type[i]))
	{
		token->value[j] = type[i];
		i++;
		j++;
	}
	return (j);
}

char	*minishell_strjoin(char const *str1, char const *str2)
{
	char	*ptr;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = ft_strlen(str1) + ft_strlen(str2) + 1;
	if (!str1)
		return ((char *)str1);
	ptr = malloc((sizeof(char) * k));
	if (!ptr)
		return (NULL);
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
	return (ptr);
}

int	assign_bracket(t_token *token, char *type, int i, char bracket)
{
	int		input_len;
	int		j;
	char	*key;
	char	*join;

	input_len = ft_strlen(type);
	j = 0;
	while (i < input_len && type[i] != bracket)
	{
		if (type[i] == '$' && bracket == '\"')
		{
			key = assign_var(token, type, i + 1);
			if (ft_strncmp(key, "", 1))
			{
				join = minishell_strjoin(token->value, key);
				printf("join: %s\n", join);
				free(token->value);
				token->value = join;
			}
			free(key);
			i += next_whitespace(type, i);
			j = ft_strlen(token->value);
		}
		else
		{
			token->value[j] = type[i];
			i++;
			j++;
		}
	}
	token->brackets = true;
	return (j);
}

t_token	check_new_cmd(t_token *token)
{
	if (token->new_cmd == true)
	{
		token->type = CMD_TOKEN;
		token->new_cmd = false;
	}
	else
		token->type = ARGUMENT_TOKEN;
	return (*token);
}
