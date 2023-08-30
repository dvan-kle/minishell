/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 13:00:29 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/08/25 17:44:36 by danielvankl   ########   odam.nl         */
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

void	test_execute(t_cmd_table *cmd_table, int pipe_count)
{
	int		fd[2];
	int		read;
	int		status;
	pid_t	child_pid;
	int		i;

	i = 0;
	read = STDIN_FILENO;
	while (i < pipe_count)
	{
		if (pipe(fd) == -1)
			exit(1);
		child_pid = fork();
		if (child_pid == -1)
			exit(1);
		if (child_pid == 0)
		{
			if (i == 0)
				red_input_and_execute(cmd_table);
			else if (i == pipe_count - 1)
				red_output_and_execute(cmd_table);
			else
			{
				dup2(read, STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				close_pipe(fd);
				execute(cmd_table->args);
			}
		}
		read = dup(fd[0]);
		waitpid(child_pid, &status, 0);
		close_pipe(fd);
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

void	test_num_exec(int num, t_cmd_table *cmd_table)
{
	if (num == 1)
		test_execute_single_cmd(cmd_table);
	if (num == 2)
		test_execute_single_pipe(cmd_table);
	if (num > 2)
		test_execute(cmd_table, num);
}