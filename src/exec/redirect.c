/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 12:52:38 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/12 16:20:59 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"
#include "../../incl/pipes.h"
#include "../../incl/redirect.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

void	redirect(t_cmd_table *cmd_table, int fd[2], int read, int index, int pipe_count)
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
		outfile = open(redirects->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirects->type == OUTPUT_REDIRECT_APPEND_TOKEN)
		outfile = open(redirects->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == 0 && !last_cmd)
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);
		return ;
	}
	if (outfile > 0)
		dup2(outfile, STDOUT_FILENO);
	close(fd[WRITE_END]);
	return ;
}

void	redirect_single(t_cmd_table *cmdtable)
{
	redirect_single_in(cmdtable->redirects);
	redirect_single_out(cmdtable->redirects);
}

void	redirect_single_in(t_redirect *redirects)
{
	int		infile;

	infile = 0;
	if (redirects->type == INPUT_REDIRECT_TOKEN)
	{
		infile = open(redirects->file, O_RDONLY);
	}
	if (infile > 0)
		dup2(infile, STDIN_FILENO);
}

void	redirect_single_out(t_redirect *redirects)
{
	int	outfile;
	int	i;

	outfile = 0;
	i = 0;
	while (redirects[i].type != END_OF_CMD_TOKEN)
	{
		if (redirects[i].type == OUTPUT_REDIRECT_TOKEN)
			outfile = open(redirects[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redirects[i].type == OUTPUT_REDIRECT_APPEND_TOKEN)
			outfile = open(redirects[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile > 0)
			dup2(outfile, STDOUT_FILENO);
		i++;
	}
}
