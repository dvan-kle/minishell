/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 13:22:39 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/26 15:10:01 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"
#include <errno.h>

void	redirect_error(char *filename)
{
	if (errno == ENOENT)
		printf("minishell: no such file or directory: %s\n", filename);
	else if (errno == EACCES)
		printf("minishell: permission denied: %s\n", filename);
	exit(EXIT_FAILURE);
}

void	execute_error(char *cmd)
{
	if (errno == ENOENT)
	{
		printf("minishell: command not found: %s\n", cmd);
		exit(127);
	}
	else if (errno == EACCES)
	{
		printf("minishell: permission denied: %s\n", cmd);
		exit(126);
	}
	else
		printf("minishell: error");
	exit(EXIT_FAILURE);
}

void	ft_free(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
