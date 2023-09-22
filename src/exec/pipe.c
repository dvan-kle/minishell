/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 13:00:29 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/21 18:09:42 by daniel        ########   odam.nl         */
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

static void	close_pipe(int pipe_fd[2])
{
	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
}

void	execute_single_cmd(t_cmd_table *cmd_table)
{
	int		status;
	pid_t	pid;

	if (check_builtin2(cmd_table) == true)
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	if (pid == 0)
	{
		ignore_signals();
		redirect_single(cmd_table);
		if (check_builtin(cmd_table, cmd_table->env_list) == true)
			execute_builtin(cmd_table, cmd_table->env_list);
		execute(cmd_table, cmd_table->env_list);
	}
	waitpid(pid, &status, 0);
}

void	execute_pipeline(t_cmd_table *cmd_table, int cmd_count, t_env_list *envl)
{
	int			fd[2];
	pid_t		pid;
	int			read;
	int			i;
	int			status;

	read = STDIN_FILENO;
	i = 0;
	while (i < cmd_count)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			ignore_signals();
			redirect(cmd_table, fd, read, i, cmd_count);
			if (check_builtin(cmd_table, envl) == true)
				execute_builtin(cmd_table, envl);
			execute(cmd_table, envl);
		}
		waitpid(pid, &status, 0);
		read = dup(fd[READ_END]);
		cmd_table = cmd_table->next;
		close_pipe(fd);
		i++;
	}
	close(read);
}

void	execute_main(t_cmd_table *cmd_table)
{
	int	stdinp;
	int	stdoutp;

	stdinp = dup(STDIN_FILENO);
	stdoutp = dup(STDOUT_FILENO);
	if (cmd_table->cmd_count == 1)
		execute_single_cmd(cmd_table);
	else
		execute_pipeline(cmd_table, cmd_table->cmd_count, cmd_table->env_list);
	dup2(stdinp, STDIN_FILENO);
	dup2(stdoutp, STDOUT_FILENO);
	close(stdinp);
	close(stdoutp);
}
