/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_single.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 16:55:30 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/13 01:14:45 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

void	redirect_single(t_cmd_table *cmd_table)
{
	int	fd_hd;

	fd_hd = heredoc(cmd_table);
	if (fd_hd > 0)
		dup2(fd_hd, STDIN_FILENO);
	redirect_single_in(cmd_table->redirects);
	redirect_single_out(cmd_table->redirects);
	if (!cmd_table->args[0])
		exit(EXIT_SUCCESS);
}

void	redirect_single_in(t_redirect *redirects)
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
		{
			outfile = open(redirects[i].file, O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
			if (outfile == -1)
				redirect_error(redirects[i].file);
		}
		else if (redirects[i].type == APPEND_TOKEN)
		{
			outfile = open(redirects[i].file, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
			if (outfile == -1)
				redirect_error(redirects[i].file);
		}
		if (outfile > 0)
			dup2(outfile, STDOUT_FILENO);
		i++;
	}
}
