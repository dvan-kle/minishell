/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <daniel@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 21:15:22 by daniel        #+#    #+#                 */
/*   Updated: 2023/10/12 17:34:17 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"
#include <readline/readline.h>

int	check_heredoc(t_cmd_table *cmd_table)
{
	t_redirect	*redirect;
	int			count;

	count = 0;
	redirect = cmd_table->redirects;
	while (redirect->type != END_OF_CMD_TOKEN)
	{
		if (redirect->type == READ_INPUT_TOKEN)
			count++;
		redirect++;
	}
	return (count);
}

char	*get_last_delim(t_cmd_table *cmd_table)
{
	char		*delim;
	t_redirect	*redirects;
	int			i;

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
			exit(130);
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
			break ;
		ft_putendl_fd(line, fd[WRITE_END]);
		free(line);
	}
	free(line);
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
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	exec_heredoc(delim, fd);
	if (infile_check(cmd_table->redirects))
		return (close_pipe(fd), 0);
	read = dup(fd[READ_END]);
	close_pipe(fd);
	return (read);
}
