/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   folders.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/29 15:18:40 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/08/22 15:35:57 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

char	**get_folders(void)
{
	char	*path;
	char	**folders;
	int		i;

	i = 0;
	path = getenv("PATH");
	folders = ft_split(path, ':');
	return (folders);
}

int	execute(char **folders, char *command_fold, char **av)
{
	char	*check_access;
	int		i = 0;
	char	**argv;

	argv = av + 1;
	while (folders[i])
	{
		check_access = ft_strjoin(folders[i], command_fold);
		if (access(check_access, X_OK) == 0)
		{
			printf("found\n");
			execve(check_access, argv, NULL);
			return (0);
		}
		i++;
	}
	printf("not found\n");
	return (-1);
}

// int	main(int ac, char **av)
// {
// 	char	**folders;
// 	char	*command_fold;
// 	// char 	**argv = { "rm", "test.txt", NULL };
// 	if (ft_strncmp(av[1], "pwd", 4) == 0)
// 	{
// 		printf("%s\n", getcwd(NULL, 0));
// 		exit (0);
// 	}
// 	else if (ft_strncmp(av[1], "clear", ft_strlen(av[1])) == 0)
// 	{
// 		printf("\033[2J\033[H");
// 		exit (0);
// 	}
// 	else if (av[1]) 
// 	{
// 		folders = get_folders();
// 		command_fold = ft_strjoin("/", av[1]);
// 		execute(folders, command_fold, av);
// 	}
// 	else
// 	{
// 		printf("command not found\n");
// 	}
// 	return (0);
// }
