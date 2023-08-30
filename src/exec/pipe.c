/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 13:00:29 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/08/30 19:31:11 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"
#include "../../incl/pipes.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	close_pipe(int pipe_fd[2])
{
	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
}

void	test_execute_single_cmd(t_cmd_table *cmd_table)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	if (pid == 0)
		execute(cmd_table->args);
	waitpid(pid, &status, 0);
}

void	test_execute_single_pipe(t_cmd_table *cmd_table)
{
	int		status;
	pid_t	child_pid;
	pid_t	child_pid2;
	int		fd[2];

	pipe(fd);
	child_pid = fork();
	if (child_pid == -1)
		exit(1);
	if (child_pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(cmd_table->args);
	}
	waitpid(child_pid, &status, 0);
	child_pid2 = fork();
	if (child_pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execute(cmd_table->next->args);
	}
	close_pipe(fd);
	waitpid(child_pid2, &status, 0);
}

void	execute_pipeline(t_cmd_table *cmd_table, int pipe_count)
{
	int		fd[2];
	pid_t	pid;
	int		read;
	int		i;

	read = 0;
	i = 0;
	while (i < pipe_count)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			dup2(read, 0);
			if (i + 1 != pipe_count)
				dup2(fd[1], 1);
			close(fd[0]);
			execute(cmd_table->args);
		}
		wait(NULL);
		close(fd[1]);
		read = fd[0];
		cmd_table = cmd_table->next;
		i++;
	}
}