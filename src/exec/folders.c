/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   folders.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/29 15:18:40 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/08/23 13:58:57 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../libft/libft.h"
#include "../../incl/exec.h"

static char	**get_folders(void)
{
	char	*path;
	char	**folders;
	int		i;

	i = 0;
	path = getenv("PATH");
	folders = ft_split(path, ':');
	return (folders);
}

int	execute(char **args)
{
	char	*check_access;
	char	*command_fold;
	int		i = 0;
	char	**folders;

	folders = get_folders();
	command_fold = ft_strjoin("/", args[0]);
	while (folders[i])
	{
		check_access = ft_strjoin(folders[i], command_fold);
		if (access(check_access, X_OK) == 0)
		{
			printf("found\n");
			execve(check_access, args, NULL);
			return (0);
		}
		i++;
	}
	printf("not found\n");
	return (-1);
}
