/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   folders.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/29 15:18:40 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/07/29 16:25:01 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

char **get_folders(void)
{
	char	*path;
	char 	**folders;
	int 	i = 0;

	path = getenv("PATH");
	folders = ft_split(path, ':');

	return (folders);
}

int execute(char **folders, char *command_fold, char **command)
{
	char	*check_access;
	int		i = 0;

	while (folders[i])
	{
		check_access = ft_strjoin(folders[i], command_fold);
		if (access(check_access, X_OK) == 0)
		{
			printf("found\n");
			execve(check_access, command, NULL);
			return (0);
		}
		i++;
	}
	printf("not found\n");
	return (-1);
}

int main(void)
{
	char	**folders;
	char	*command_fold;
	char 	*command[] = { "mkdir", "testmap2", NULL };

	folders = get_folders();
	command_fold = "/mkdir";
	execute(folders, command_fold, command);
	return (0);
}
