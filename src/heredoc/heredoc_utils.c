/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <daniel@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 21:15:22 by daniel        #+#    #+#                 */
/*   Updated: 2023/10/11 23:26:08 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"
#include <readline/readline.h>

int	check_heredoc(t_cmd_table *cmd_table)
{
	t_redirect	*redirect;
	int			count;

	count = 0;
	while(cmd_table)
	{
		redirect = cmd_table->redirects;
		while (redirect->type != END_OF_CMD_TOKEN)
		{
			if (redirect->type == READ_INPUT_TOKEN)
				count++;
			redirect++;
		}
		cmd_table = cmd_table->next;
	}
	return (count);
}

char	*get_last_delim(t_cmd_table *cmd_table)
{
	char		*delim;
	t_redirect	*redirects;
	int		i;

	i = 0;
	while (cmd_table)
	{
		redirects = cmd_table->redirects;
		while (redirects[i].type != END_OF_CMD_TOKEN)
		{
			if (redirects[i].type == READ_INPUT_TOKEN)
				delim = redirects[i].file;
			i++;
		}
		cmd_table = cmd_table->next;
	}
	return (delim);
}

void	exec_heredoc(char *delim, int fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
			break ;
		ft_putendl_fd(line, fd[WRITE_END]);
		free(line);
	}
	free(line);
}

int	heredoc(t_cmd_table *cmd_table)
{
	char	*delim;
	int		check;
	int		fd[2];
	int		read;

	check = check_heredoc(cmd_table);
	if (!check)
		return (0);
	delim = get_last_delim(cmd_table);
	pipe(fd);
	exec_heredoc(delim, fd);
	read = dup(fd[READ_END]);
	close_pipe(fd);
	return (read);
}
