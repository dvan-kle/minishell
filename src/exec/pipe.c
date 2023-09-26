/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 13:00:29 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/26 15:21:54 by daniel        ########   odam.nl         */
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

int	execute_single_cmd(t_cmd_table *cmd_table)
{
	int		status;
	pid_t	pid;
	int		exit_status;

	if (check_builtin(cmd_table) == true)
	{
		redirect_single(cmd_table);
		execute_builtin(cmd_table);
		exit_status = EXIT_SUCCESS;
		return (exit_status); 
	}
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
		execute(cmd_table, cmd_table->env_list);
	}
	waitpid(pid, &status, 0);
	exit_status = WEXITSTATUS(status);
	return (exit_status);
}

int	execute_pipeline(t_cmd_table *cmd_table, int cmd_count, t_env_list *envl)
{
	int			fd[2];
	pid_t		pid;
	int			read;
	int			i;
	int			status;
	int			exit_status;

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
			if (check_builtin(cmd_table) == true)
				execute_builtin(cmd_table);
			execute(cmd_table, envl);
		}
		waitpid(pid, &status, 0);
		exit_status = WEXITSTATUS(status);
		close(read);
		read = dup(fd[READ_END]);
		cmd_table = cmd_table->next;
		close_pipe(fd);
		i++;
	}
	close(read);
	return (exit_status);
}	

int	execute_main(t_cmd_table *cmd_table)
{
	int	stdin;
	int	stdout;
	int exit_status;

	
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	if (cmd_table->cmd_count == 1)
		exit_status = execute_single_cmd(cmd_table);
	else
		exit_status = execute_pipeline(cmd_table, cmd_table->cmd_count, cmd_table->env_list);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
	return (exit_status);
}
