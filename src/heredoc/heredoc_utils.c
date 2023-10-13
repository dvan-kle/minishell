/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <daniel@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 21:15:22 by daniel        #+#    #+#                 */
/*   Updated: 2023/10/13 12:06:28 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"
#include <readline/readline.h>

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

char	*get_last_delim(t_cmd_table *cmd_table, int i)
{
	char		*delim;
	t_redirect	*redirects;

	delim = NULL;
	redirects = cmd_table->redirects;
	while (redirects[i].type != END_OF_CMD_TOKEN)
	{
		if (redirects[i].type == READ_INPUT_TOKEN)
		{
			delim = redirects[i].file;
			break ;
		}
		i++;
	}
	return (delim);
}

void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(EXIT_FAILURE);
	}
}

bool	infile_check(t_redirect *head)
{
	t_redirect	*redirects;
	t_redirect	*tmp;
	int			count;

	tmp = head;
	redirects = head;
	count = 0;
	while (tmp[count].type != END_OF_CMD_TOKEN)
		count++;
	while (count > 0)
	{
		if (redirects[count - 1].type == INPUT_REDIRECT_TOKEN)
			return (true);
		if (redirects[count - 1].type == READ_INPUT_TOKEN)
			return (false);
		count--;
	}
	return (true);
}
