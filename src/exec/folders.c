/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   folders.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/29 15:18:40 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/06 14:14:20 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../libft/libft.h"
#include "../../incl/exec.h"

static char	*check_access(char **folders, char *cmd)
{
	char	*check_access;
	char	*command_fold;
	int		i;

	i = 0;
	command_fold = ft_strjoin("/", cmd);
	while (folders[i])
	{
		check_access = ft_strjoin(folders[i], command_fold);
		// dprintf(2, "check_access: %s\n", check_access);
		if (access(check_access, X_OK) == 0)
		{
			// dprintf(2, "check_access: ok!\n");
			return (check_access);
		}
		i++;
	}
	if (access(cmd, X_OK) == 0)
		return (cmd);
	return (cmd);
}

static char	*get_path(t_env_list *env_list, char *cmd)
{
	char	*path;
	char	**folders;

	while (env_list != NULL)
	{
		if (ft_strncmp(env_list->key, "PATH", 5) == 0)
		{
			// dprintf(2, "key: %s\n", env_list->key);
			path = env_list->value;
		}
		env_list = env_list->next;
	}
	// dprintf(2, "path: %s\n", path);
	folders = ft_split(path, ':');
	path = check_access(folders, cmd);
	return (path);
}

int	execute(char **args, t_env_list *env_list)
{
	char	*path;

	path = get_path(env_list, args[0]);
	if (access(path, X_OK) != 0)
	{
		printf("minishell: command not found: %s\n", args[0]);
		return (0);
	}
	execve(path, args, NULL);
	return (0);
}
