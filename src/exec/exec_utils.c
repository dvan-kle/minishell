/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 16:49:17 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/07 23:46:56 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"
#include "../../incl/exec.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t	*create_pid_array(int cmd_count)
{
	pid_t	*pid_array;
	int		i;

	i = 0;
	pid_array = ft_malloc(sizeof(pid_t) * cmd_count);
	while (i < cmd_count)
	{
		pid_array[i] = 0;
		i++;
	}
	return (pid_array);
}

int	wait_all_pids(pid_t *pid_array, int cmd_count)
{
	int	i;
	int	status;
	int	exit_status;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pid_array[i], &status, 0);
		exit_status = WEXITSTATUS(status);
		i++;
	}
	free(pid_array);
	return (exit_status);
}