/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 13:22:39 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/23 17:35:35 by daniel        ########   odam.nl         */
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
		printf("minishell: command not found: %s\n", cmd);
	else if (errno == EACCES)
		printf("minishell: permission denied: %s\n", cmd);
	else
		printf("minishell: error");
	exit(EXIT_FAILURE);
}

void	ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
