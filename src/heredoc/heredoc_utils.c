/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <daniel@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 21:15:22 by daniel        #+#    #+#                 */
/*   Updated: 2023/10/10 14:53:55 by dvan-kle      ########   odam.nl         */
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
	delim = cmd_table->redirects->file;
	pipe(fd);
	exec_heredoc(delim, fd);
	read = dup(fd[READ_END]);
	close_pipe(fd);
	return (read);
}
