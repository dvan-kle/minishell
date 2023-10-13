/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredox_expand.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 16:38:21 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/12 16:41:37 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

char	*heredoc_var(char *line, int i, t_env_list *env_lst)
{
	char		*key;
	t_env_list	*temp;

	key = ft_substr(line, i, next_whitespace_brackets(line, i));
	temp = env_lst;
	while (temp)
	{
		if (!ft_strncmp(temp->key, key, ft_strlen(key) + 1))
		{
			free(key);
			return (ft_strdup(temp->value));
		}
		temp = temp->next;
	}
	free(key);
	return (ft_strdup(""));
}

char	*expand_heredoc(char *line, t_env_list *env_lst)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$')
		{
			ret = minishell_strjoin(ret, heredoc_var(line, i + 1, env_lst));
			i += next_whitespace_brackets(line, i + 1) + 1;
		}
		else
		{
			ret = ft_charjoin(ret, line[i]);
			i++;
		}
	}
	free(line);
	return (ret);
}
