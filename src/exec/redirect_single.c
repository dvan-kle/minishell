#include "../../incl/main.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

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