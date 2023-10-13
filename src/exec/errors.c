/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 13:22:39 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/13 12:55:48 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

void	redirect_error(char *filename)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putendl_fd(filename, 2);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishell: permission denied: ", 2);
		ft_putendl_fd(filename, 2);
	}
	exit(EXIT_FAILURE);
}

void	execute_error(char *cmd)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putendl_fd(cmd, 2);
		exit(127);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishell: permission denied: ", 2);
		ft_putendl_fd(cmd, 2);
		exit(126);
	}
	else
		ft_putendl_fd("minishell: error", 2);
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
