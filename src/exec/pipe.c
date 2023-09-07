/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 13:00:29 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/07 14:51:03 by dvan-kle      ########   odam.nl         */
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

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	if (pid == 0)
		execute(cmd_table->args, cmd_table->env_list);
	waitpid(pid, &status, 0);
}

void	execute_pipeline(t_cmd_table *cmd_table, int cmd_count, t_env_list *env_list)
{
	int			fd[2];
	pid_t		pid;
	int			read;
	int			i;
	int			status;

	env_list = cmd_table->env_list;
	read = STDIN_FILENO;
	i = 0;
	while (i < cmd_count)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			redirect(cmd_table, fd, read, i, cmd_count);
			execute(cmd_table, env_list);
		}
		waitpid(pid, &status, 0);
		read = dup(fd[READ_END]);
		cmd_table = cmd_table->next;
		close_pipe(fd);
		i++;
	}
}

void	execute_main(t_cmd_table *cmd_table)
{
	int	stdin;
	int	stdout;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	execute_pipeline(cmd_table, cmd_table->cmd_count, cmd_table->env_list);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
}

// void	execute_pipeline(t_cmd_table *cmd_table, int pipe_count)
// {
// 	int			fd[2];
// 	pid_t		pid;
// 	int			read;
// 	int			i;
// 	int			status;

// 	read = STDIN_FILENO;
// 	i = 0;
// 	while (i < pipe_count)
// 	{
// 		pipe(fd);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			dup2(read, STDIN_FILENO);
// 			if (i + 1 != pipe_count)
// 				dup2(fd[WRITE_END], STDOUT_FILENO);
// 			close(fd[READ_END]);
// 			execute(cmd_table->args);
// 		}
// 		waitpid(pid, &status, 0);
// 		close(fd[WRITE_END]);
// 		read = dup(fd[READ_END]);
// 		cmd_table = cmd_table->next;
// 		i++;
// 	}
// }