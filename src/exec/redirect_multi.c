/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_multi.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 12:52:38 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/09 21:31:34 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

void	redirect(t_cmd_table *cmd_table, int fd[2], int read,
			int index, int pipe_count)
{
	bool	last_cmd;

	close(fd[READ_END]);
	if (index == pipe_count - 1)
		last_cmd = true;
	else
		last_cmd = false;
	redirect_in(cmd_table->redirects, read);
	redirect_out(cmd_table->redirects, fd, last_cmd);
}

void	redirect_in(t_redirect *redirects, int read)
{
	int		infile;

	infile = 0;
	if (redirects->type == INPUT_REDIRECT_TOKEN)
	{
		infile = open(redirects->file, O_RDONLY);
		if (infile == -1)
			redirect_error(redirects->file);
	}
	if (infile > 0)
		dup2(infile, STDIN_FILENO);
	else
		dup2(read, STDIN_FILENO);
}

void	redirect_out(t_redirect *redirects, int fd[2], bool last_cmd)
{
	int		outfile;

	outfile = 0;
	close(fd[READ_END]);
	if (redirects->type == OUTPUT_REDIRECT_TOKEN)
	{
		outfile = open(redirects->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			redirect_error(redirects->file);
	}
	else if (redirects->type == APPEND_TOKEN)
	{
		outfile = open(redirects->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile == -1)
			redirect_error(redirects->file);
	}
	if (outfile == 0 && !last_cmd)
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		return ;
	}
	if (outfile > 0)
		dup2(outfile, STDOUT_FILENO);
	close(fd[WRITE_END]);
}
