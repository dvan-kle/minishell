/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <daniel@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 01:18:36 by daniel        #+#    #+#                 */
/*   Updated: 2023/10/13 01:24:19 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"
#include "readline/readline.h"

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

void	exec_heredoc(char *delim, int fd[2], int count, t_env_list *env_lst)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, signal_heredoc);
		line = readline("> ");
		if (!line)
			exit(EXIT_FAILURE);
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
			break ;
		if (count == 0)
		{
			line = expand_heredoc(line, env_lst);
			ft_putendl_fd(line, fd[WRITE_END]);
		}
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
	int		i;

	i = 0;
	check = check_heredoc(cmd_table);
	if (!check)
		return (0);
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	while (check > 0)
	{
		delim = get_last_delim(cmd_table, i);
		exec_heredoc(delim, fd, --check, cmd_table->env_list);
		i++;
	}
	if (infile_check(cmd_table->redirects))
		return (close_pipe(fd), 0);
	read = dup(fd[READ_END]);
	close_pipe(fd);
	return (read);
}
