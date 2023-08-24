/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 13:00:29 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/08/24 17:27:09 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "../../incl/main.h"
#include "../../incl/pipes.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void	close_pipe(int pipe_fd[2])
{
	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
}

void	execute_child(int pipe_fd[2], t_cmd_table *cmd_table)
{
	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	close_pipe(pipe_fd);
	execute(cmd_table->args);
}

void	test_execute(t_cmd_table *cmd_table)
{
	int		pipe_fd[2];
	int		read;
	int 	status;
	pid_t	child_pid;
	int		i;

	i = 0;
	read = STDOUT_FILENO;
	while (i < 2)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("Pipe failed");
			exit(1);
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Fork failed");
			exit(1);
		}
		if (child_pid == 0)
			execute_child(pipe_fd, cmd_table);
		waitpid(child_pid, &status, 0);
		i++;
	}
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
	child_pid2 = fork();
	if (child_pid == -1)
		exit(1);
	if (child_pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(cmd_table->args);
	}
	if (child_pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execute(cmd_table->next->args);
	}
	close_pipe(fd);
	waitpid(child_pid, &status, 0);
	waitpid(child_pid2, &status, 0);
}
