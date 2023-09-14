/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assign_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 18:56:56 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/14 15:12:14 by tde-brui      ########   odam.nl         */
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

void	assign_minus(t_token *token, char *type, int i)
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
	token->value[j] = '\0';
}

char	*ft_charjoin(char *str, char c)
{
	char	*ret;
	int		i;

	ret = ft_malloc(sizeof(char) * ft_strlen(str) + 2);
	i = 0;
	if (!str)
	{
		ret[0] = c;
		ret[1] = '\0';
		return (ret);
	}
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	free(str);
	return (ret);
}

void	assign_bracket(t_token *token, char *type, int i, char bracket)
{
	int		input_len;
	char	*key;

	input_len = ft_strlen(type);
	token->value = ft_strdup("");
	while (i < input_len && type[i] != bracket)
	{
		if (type[i] == '$' && bracket == '\"')
		{
			key = assign_var(token, type, i + 1);
			token->value = ft_strjoin(token->value, key);
			i += next_whitespace(type, i);
		}
		else
		{
			token->value = ft_charjoin(token->value, type[i]);
			i++;
		}
	}
	token->brackets = true;
}
